/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:00:06 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 19:54:13 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/wait.h>
#include <cstring>
#include <stdlib.h>
#include "Logger.hpp"
#include "Response.hpp"
#include "ServerInstanceConfig.hpp"
#include "Request.hpp"

typedef ServerInstanceConfig::LocationConfig Location;

class CgiHandler {
  public:
	CgiHandler(Logger *);
	~CgiHandler();

    std::string execute(const std::string& scriptPath, const std::string& requestData);

	void createResponse(Response& response, Request& request, Location& location, ServerInstanceConfig& config);

  private:
	char* _envp[30];
	Logger* _logger;

	void setupEnvVars(Request &request);

	// Response _response;
	// Request& _request;
	// Location& _location;
	// ServerInstanceConfig& _config;

	CgiHandler();
	CgiHandler(const CgiHandler&);
	CgiHandler& operator=(CgiHandler const&);
};
