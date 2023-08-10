/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:28:47 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/10 12:47:11 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

class Responder;
#include "MyException.hpp"
#include "Request.hpp"
#include "Logger.hpp"
#include "ServerInstanceConfig.hpp"
#include "ErrorPages.hpp"
#include "Response.hpp"
#include "CgiHandler.hpp"
#include "Webserv.hpp"

class Responder
{
  public:
  	Responder();
	Responder(Logger* logger);
	~Responder();
	Responder(const Responder &);
	Responder& operator=(const Responder &);
	
	Response getResponse(Request& request, ServerInstanceConfig& serverConf);
  private:
	Logger* _logger;

	LocationConfig* isCgiRequest(Request& request, ServerInstanceConfig& serverConf);
	void indexDirectory(std::string path, Response& response);
};
