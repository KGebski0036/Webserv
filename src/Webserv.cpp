/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:57 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/10 15:13:06 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"

void Webserv::setup()
{
	_biggestFd = 0;
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

		int result = select(_biggestFd + 1, &recvSetCpy, &writeSetCpy, NULL, &timer);

		if (result < 0 )
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
			if (FD_ISSET(i, &writeSetCpy))
				sendHttpResponse(i);
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
	char buffer[MESSAGE_BUFFER + 1];
	std::string tmp = "";
	
	int ret;
	while ((ret = recv(fd, buffer, MESSAGE_BUFFER, MSG_DONTWAIT)) > 0)
	{
		buffer[ret] = 0;
		if (tmp.size() == 0)
		{
			std::string host;
			std::string bufferTmp = buffer;
			int pos = bufferTmp.find("Host:");
			host = bufferTmp.substr(pos + 6, bufferTmp.find("\n", pos) - pos);
			_clientsMap[fd].server = getServerByIP(host);
		}
		tmp += buffer;
		if ((tmp.size() - tmp.find("\r\n\r\n") - 3) > _clientsMap[fd].server.clientBodyBufferSize)
		{
			_logger->print(INFO, "Client has exceeded the maximum clientBodyBufferSize, max allowed: " + std::to_string(_clientsMap[fd].server.clientBodyBufferSize) + " client request body size was: " + std::to_string(tmp.size() - tmp.find("\r\n\r\n") - 3), 1);
			_clientsMap[fd].response.code = 400;
			FD_CLR(fd, &_recvFdPool);
			FD_SET(fd, &_writeFdPool);
			return;
		}
	}

	FD_CLR(fd, &_recvFdPool);
	_clientsMap[fd].request = Request(tmp);
	_logger->print(INFO, "New request picked up: \n" + std::string(DIM) + _clientsMap[fd].request.toString(), 0);

	FD_SET(fd, &_writeFdPool);
}

void Webserv::sendHttpResponse(int clientSockfd)
{
	Client& client = _clientsMap[clientSockfd];

	if (client.response.code == 200)
		client.response = _responder->getResponse(client.request, client.server);

	std::string httpResponse = "HTTP/1.1 " + ErrorPages::getHttpStatusMessage(client.response.code)  + "\r\n";
	
	if (client.response.code == 200)
	{
		httpResponse += "Content-Length: " + std::to_string(client.response.length()) + "\r\n";
		httpResponse += "Content-Type: " + MIMEtypes::getMIMEtype(client.request.getPath()) + "\r\n";
		httpResponse += "Set-Cookie: interesting=https://youtu.be/dQw4w9WgXcQ\r\n";
		httpResponse += "\r\n";
		httpResponse += client.response.body;
	}
	else
	{
		std::string tmp = ErrorPages::generateErrorPage(client.response.code, client.server);
		httpResponse += "Content-Length: " + std::to_string(tmp.length()) + "\r\n";
		httpResponse += "Content-Type: text/html\r\n";
		httpResponse += "\r\n";
		httpResponse += tmp;
	}

	if (send(clientSockfd, httpResponse.c_str(), httpResponse.length(), 0) <= 0) {
		closeConnection(clientSockfd);
	}
	closeConnection(clientSockfd);
}

ServerInstanceConfig& Webserv::getServerByIP(std::string host)
{
	std::string ip = host.substr(0, host.find(":"));
	int port = std::atoi(host.substr(host.find(":") + 1).c_str());

	for (std::map<int, ServerInstanceConfig>::iterator it = _serversMap.begin(); it != _serversMap.end(); ++it)
	{
		if ((it->second.listenAddress == ip || it->second.listenAddress == "0.0.0.0" || it->second.serverName == ip) && it->second.port == port)
			return it->second;
	}
	_logger->print(INFO, std::string(SYS_MSG) +  std::string(GREEN) +  std::string(DIM) + "Default server used", 0);
	return (_serversMap.begin()->second);
}

void Webserv::closeConnection(int fd)
{
	if (FD_ISSET(fd, &_writeFdPool))
		FD_CLR(fd, &_writeFdPool);
	if (FD_ISSET(fd, &_recvFdPool))
		FD_CLR(fd, &_recvFdPool);
	close(fd);
	_clientsMap.erase(fd);
}

void Webserv::clean()
{

}

Webserv::Webserv(Config& input, Logger* logger) : _logger(logger), _serversConfigs(input.getServersConfigs()) {
	_responder = new Responder(_logger);
	FD_ZERO(&_recvFdPool);
    FD_ZERO(&_writeFdPool);
}

Webserv::~Webserv() {
	delete _responder;
}

Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }
