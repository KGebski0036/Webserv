/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 17:18:03 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 17:25:36 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

Client::Client(int sockFd) : _clientSocket(sockFd) {}

Client::Client() {}
Client::~Client() {}
Client::Client(const Client& src) { (void)src; }

Client& Client::operator=(Client const& src)
{
	if (this != &src)
		_clientSocket = src._clientSocket;
	return *this; 
}
