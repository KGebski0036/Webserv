/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/10 13:35:47 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <csignal>

#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"
#include "Client.hpp"
#include "ServerInstanceConfig.hpp"
#include "Responder.hpp"

#define TIMEOUT 10
#define MAX_CLIENTS 512
#define MESSAGE_BUFFER 10000

class Webserv {
  public:
	Webserv(Config&, Logger*);
	~Webserv();

	void setup();

	void run();

	void clean();
  private:

	Logger* _logger;
	Responder* _responder;
	std::vector<ServerInstanceConfig> _serversConfigs;
	std::map<int, ServerInstanceConfig> _serversMap;
    std::map<int, Client> _clientsMap;

    int _biggestFd;
	fd_set _recvFdPool;
    fd_set _writeFdPool;

	void acceptNewConnection(ServerInstanceConfig &);
	void readRequest(int);
	void sendHttpResponse(int clientSockfd);
	void closeConnection(int fd);
	ServerInstanceConfig& getServerByIP(std::string host);

	Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
};
