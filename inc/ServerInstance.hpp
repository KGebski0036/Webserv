/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:31:19 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 15:38:28 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sys/socket.h>
#include <cstring>
# include <stdio.h>
#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>
#include <fcntl.h>
class ServerInstance;
#include "ErrorPages.hpp"

class ServerInstance : public MyException {
  public:
	ServerInstance(const ServerInstanceConfig& instanceConfig);
	~ServerInstance();

	// void config(std::string pathToFile);
	int	 setup();
	void run();
	void clean();
	int createSocket();
	std::string getResponse(std::string buffer);
	void sendHttpResponse(int clientSockfd, const std::string& response); //! TO BE DELETED
	int const & getResponseCode() const;

  private:
	int _socketFd;
  	const ServerInstanceConfig& _instanceConfig;
	int	_response_code;
	
	ServerInstance(const ServerInstance&);
	ServerInstance& operator=(ServerInstance const &);
};
