/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:57 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 13:03:10 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"


int	 Webserv::setup()
{
	for (size_t i = 0; i < _serversConfigs.size(); ++i)
	{
		createSockets
	}
	return 0;
}

int Webserv::createSockets(ServerInstanceConfig instanceConfig) {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1)
		throw MyException("Socket creation failed", __func__, __FILE__, __LINE__);


	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(instanceConfig.listenAddress.c_str());
	serverAddr.sin_port = htons(instanceConfig.port);

	if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw MyException("Binding the socket failed", __func__, __FILE__, __LINE__);

	return sockfd;
}

void Webserv::run()
{
	
}

void Webserv::clean()
{

}

Webserv::Webserv(Config& input) : _serversConfigs(input.getServersConfigs()) {}

Webserv::~Webserv() {}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }
