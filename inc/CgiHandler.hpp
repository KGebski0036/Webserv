/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:00:06 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 19:47:33 by cjackows         ###   ########.fr       */
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
#include <signal.h>
#include "Logger.hpp"
#include "Response.hpp"
#include "ServerInstanceConfig.hpp"
#include "Request.hpp"
#include "MyException.hpp"

class CgiHandler {
  public:
	CgiHandler(Logger *);
	~CgiHandler();

    std::string execute(const std::string scriptPath, Response& response, Request& request);

	void createResponse(Response& response, Request& request, LocationConfig& location, ServerInstanceConfig& config);

  private:
	Logger* _logger;

	char** setupEnvVars(Request &request);

	CgiHandler();
	CgiHandler(const CgiHandler&);
	CgiHandler& operator=(CgiHandler const&);
};
