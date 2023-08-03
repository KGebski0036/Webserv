/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 17:31:45 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"
#include "Client.hpp"
#include "ServerInstanceConfig.hpp"


#define MAX_CLIENTS 512

class Webserv {
  public:
	Webserv(Config&, Logger&);
	~Webserv();

	void setup();

	void run();

	void clean();
  private:

	Logger* _logger;
	std::vector<ServerInstanceConfig> _serversConfigs;
	std::map<int, ServerInstanceConfig> _serversMap;
    std::map<int, Client> _clientsMap;

    int _biggestFd;
	fd_set _recvFdPool;
    fd_set _writeFdPool;

	void acceptNewConnection(ServerInstanceConfig &);

	Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
};
