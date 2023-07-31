/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:33:29 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 19:45:48 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ServerInstance.hpp"


// void ServerInstance::config()
// {
// 	_config = Config::readConfig(pathToFile);
// 	for (size_t i = 0; i < _config->getServersConfigs().size(); i++)
// 		std::cout << SYS_MSG << "Server config[" << i + 1 << "]" << E << _config->getServersConfigs()[i] << E;
// }

int	 ServerInstance::setup()
{
	
	try
	{
		_socketFd = createSocket();
		std::cout << "socket fd" << _socketFd << E;
	} catch (const MyException &e) { std::cerr << e.what();}
	return 0;
}
		
void ServerInstance::run()
{
	std::vector<struct pollfd> clientFds(MAX_CLIENTS + 1);
	clientFds[0].fd = _socketFd;
	clientFds[0].events = POLLIN; // Monitor for incoming connections
	int numSockets = 1;

	if (listen(_socketFd, SOMAXCONN) == -1)
		throw MyException("Listen on the socket failed", __func__, __FILE__, __LINE__);

	while(42) {
		int ready = poll(&clientFds[0], numSockets, -1);

		if (ready == -1)
			throw MyException("Error while polling for events", __func__, __FILE__, __LINE__);

		if (clientFds[0].revents & POLLIN) {
			struct sockaddr_in clientAddr;
			socklen_t clientAddrLen = sizeof(clientAddr);
			int clientSockfd = accept(_socketFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
			if (clientSockfd == -1) {
				perror("accept");
			} else {
				// Add client socket to pollfd array
				if (numSockets == MAX_CLIENTS + 1) {
					std::cerr << "Maximum number of clients reached. Rejecting new connection." << std::endl;
					close(clientSockfd);
				} else {
					clientFds[numSockets].fd = clientSockfd;
					clientFds[numSockets].events = POLLIN; // Monitor for incoming data
					++numSockets;
				}
			}
		}

		for (int i = 1; i < numSockets; ++i) {
			if (clientFds[i].revents & POLLIN) {
				// handleClientData(clientFds[i].fd);
				char buffer[8000];
				int r = read(clientFds[i].fd, buffer, sizeof(buffer));
				buffer[r] = '\0';
				if (r > 0)
					std::cout << buffer << E;
					// TODO PArsing the request
				// std::cout << SYS_MSG << "Connection from client " << E;
			}
		}
	}

}

void ServerInstance::clean()
{

}

int ServerInstance::createSocket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
		throw MyException("Socket creation failed", __func__, __FILE__, __LINE__);


	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(_instanceConfig.listenAddress.c_str());
	serverAddr.sin_port = htons(_instanceConfig.port);

	if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw MyException("Binding the socket failed", __func__, __FILE__, __LINE__);

	return sockfd;
}


ServerInstance::ServerInstance(const ServerInstanceConfig& instanceConfig) : _instanceConfig(instanceConfig) {
	try {
		setup();
		run();
	} catch (const MyException &e) { std::cerr << e.what();}
}

ServerInstance::~ServerInstance() {}

ServerInstance::ServerInstance(const ServerInstance& src)  : _instanceConfig(src._instanceConfig) { (void)src; }
ServerInstance& ServerInstance::operator=(ServerInstance const& src) { (void)src; return *this; }
