/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:57 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 18:56:03 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"

void Webserv::setup()
{
	_logger->print(INFO, "Servers are being initialized", 0);
	for (size_t i = 0; i < _serversConfigs.size(); ++i)
	{
		_logger->print(INFO, "Config for server \"" + _serversConfigs[i].serverName + "\"loaded succesfully.", 0);
		std::stringstream ss;
		ss << _serversConfigs[i];
		_logger->print(INFO, DIM ,ss.str() , 0);

		_serversConfigs[i].listen_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (_serversConfigs[i].listen_fd == -1)
			throw MyException("Socket creation failed for server \"" + _serversConfigs[i].serverName + "\"", __func__, __FILE__, __LINE__);

		int option_value = 1;
		setsockopt(_serversConfigs[i].listen_fd, SOL_SOCKET, SO_REUSEADDR, &option_value, sizeof(int));
		_serversConfigs[i].serverAddr.sin_family = AF_INET;
		_serversConfigs[i].serverAddr.sin_addr.s_addr = inet_addr(_serversConfigs[i].listenAddress.c_str());
		_serversConfigs[i].serverAddr.sin_port = htons(_serversConfigs[i].port);

		if (bind(_serversConfigs[i].listen_fd, (struct sockaddr*)&_serversConfigs[i].serverAddr, sizeof(_serversConfigs[i].serverAddr)) == -1)
			throw MyException("Binding the socket failed for server " + _serversConfigs[i].serverName, __func__, __FILE__, __LINE__);

		if (listen(_serversConfigs[i].listen_fd, MAX_CLIENTS) == -1)
			throw MyException("Listen on the socket failed for server " + _serversConfigs[i].serverName, __func__, __FILE__, __LINE__);
		
		if (fcntl(_serversConfigs[i].listen_fd, F_SETFL, O_NONBLOCK) < 0)
			throw MyException("Setting non-blocking mode on the socket failed for server " + _serversConfigs[i].serverName, __func__, __FILE__, __LINE__);

		FD_SET(_serversConfigs[i].listen_fd, &_recvFdPool);
		if (_serversConfigs[i].listen_fd > _biggestFd)
			_biggestFd = _serversConfigs[i].listen_fd;

        _serversMap.insert(std::make_pair(_serversConfigs[i].listen_fd, _serversConfigs[i]));
		_logger->print(INFO, GREEN, "Server: \"http://" + _serversConfigs[i].listenAddress + ":" + std::to_string(_serversConfigs[i].port)  + "\" initialized succesfully.", 0);
	}
}

void Webserv::run()
{
	struct timeval timer;
	timer.tv_sec = 1;
	timer.tv_usec = 0;
	while (42)
	{
    	fd_set recvSetCpy = _recvFdPool;
    	fd_set writeSetCpy = _writeFdPool;

		if ((select(_biggestFd + 1, &recvSetCpy, &writeSetCpy, NULL, &timer)) < 0 )
		    throw MyException("Select failed", __func__, __FILE__, __LINE__);

		for (int i = 0; i <= _biggestFd ; ++i)
		{
			if (FD_ISSET(i, &recvSetCpy))
			{
				if (_serversMap.count(i))
            		acceptNewConnection(_serversMap.find(i)->second);
				else
					readRequest(i);
			}
		}
	}
}

void Webserv::acceptNewConnection(ServerInstanceConfig& serv)
{
	struct sockaddr_in clientAddress;
	long socklen = sizeof(clientAddress);
	int clientSock;
	
	if ((clientSock = accept(serv.listen_fd, (struct sockaddr *)&clientAddress, (socklen_t*)&socklen)) == -1)
		throw MyException("Accept failed", __func__, __FILE__, __LINE__);

	FD_SET(clientSock, &_recvFdPool);
	if (clientSock > _biggestFd)
		_biggestFd = clientSock;

	if (fcntl(clientSock, F_SETFL, O_NONBLOCK) < 0)
	{
		FD_CLR(clientSock, &_recvFdPool);
		close(clientSock);
		throw MyException("Fcntl failed", __func__, __FILE__, __LINE__);
	}

	Client bob(clientSock);

	if (_clientsMap.count(clientSock) != 0)
        _clientsMap.erase(clientSock);

	_clientsMap[clientSock] = bob;

    char str[INET_ADDRSTRLEN];
	_logger->print(INFO, "New connection accepted " + std::string(inet_ntop(AF_INET, &(clientAddress.sin_addr), str, INET_ADDRSTRLEN)), 0);
}

void Webserv::readRequest(int fd)
{
	char    buffer[MESSAGE_BUFFER];
	int ret = recv(fd, buffer, MESSAGE_BUFFER, MSG_DONTWAIT);
	buffer[ret] = 0;
	if (ret < 0)
	{
		closeConnection(fd);
		throw MyException("Fcntl failed", __func__, __FILE__, __LINE__);
	}
	else if (ret == 0)
	{
		closeConnection(fd);
		return;
	}

	_logger->print(INFO, "New request picked up: \n" + std::string(DIM) + std::string(buffer), 0);
}

void Webserv::closeConnection(int fd)
{
	if (FD_ISSET(fd, &_writeFdPool))
		FD_CLR(fd, &_recvFdPool);
	if (FD_ISSET(fd, &_recvFdPool))
		FD_CLR(fd, &_recvFdPool);
	close(fd);
	_clientsMap.erase(fd);
}

void Webserv::clean()
{

}

Webserv::Webserv(Config& input, Logger* logger) : _logger(logger), _serversConfigs(input.getServersConfigs()) {
	FD_ZERO(&_recvFdPool);
    FD_ZERO(&_writeFdPool);
}

Webserv::~Webserv() {}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }
