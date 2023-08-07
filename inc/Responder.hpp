/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:28:47 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/07 18:58:52 by kgebski          ###   ########.fr       */
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
	void indexDirectory(std::string path, Response& response);
};
