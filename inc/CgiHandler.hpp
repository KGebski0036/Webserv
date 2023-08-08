/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:00:06 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/08 15:23:44 by cjackows         ###   ########.fr       */
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

class CgiHandler {
  public:
	CgiHandler(Logger *);
	~CgiHandler();

    std::string execute(const std::string scriptPath);

	void createResponse(Response& response, Request& request, LocationConfig& location, ServerInstanceConfig& config);

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
