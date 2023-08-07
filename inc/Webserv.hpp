/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 17:53:27 by kgebski          ###   ########.fr       */
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
	ServerInstanceConfig& getServerByIP(Request request);

	Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
};
