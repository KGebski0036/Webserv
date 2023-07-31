/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:33:29 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 18:58:32 by cjackows         ###   ########.fr       */
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

	if (listen(sockfd, SOMAXCONN) == -1)
		throw MyException("Listen on the socket failed", __func__, __FILE__, __LINE__);

ServerInstance::ServerInstance(const ServerInstanceConfig& instanceConfig) : _instanceConfig(instanceConfig) {
	try {
		setup();
	} catch (const MyException &e) { std::cerr << e.what();}
}

ServerInstance::~ServerInstance() {}

ServerInstance::ServerInstance(const ServerInstance& src)  : _instanceConfig(src._instanceConfig) { (void)src; }
ServerInstance& ServerInstance::operator=(ServerInstance const& src) { (void)src; return *this; }
