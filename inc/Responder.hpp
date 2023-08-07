/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:28:47 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/07 06:02:46 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

#include "MyException.hpp"
#include "Request.hpp"
#include "Logger.hpp"
#include "ServerInstanceConfig.hpp"
#include "ErrorPages.hpp"
#include "Response.hpp"
#include "CgiHandler.hpp"

typedef ServerInstanceConfig::LocationConfig Location;

class Responder
{
  public:
  	Responder();
	Responder(Logger* logger);
	~Responder();
	Responder(const Responder &);
	Responder& operator=(const Responder &);
	
	Response getResponse(Request& request, ServerInstanceConfig serverConf);
  private:
	Logger* _logger;

	Location* isCgiRequest(Request& request, ServerInstanceConfig serverConf);
	void indexDirectory(std::string path, ServerInstanceConfig serverConf, Response& response);
	void return404Page(Response& response, ServerInstanceConfig serverConf, std::string path);
};
