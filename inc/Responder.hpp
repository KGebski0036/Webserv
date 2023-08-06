/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:28:47 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/06 20:29:20 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include <string>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <sys/stat.h>

#include "Request.hpp"
#include "Logger.hpp"
#include "ServerInstanceConfig.hpp"
#include "ErrorPages.hpp"
#include "Response.hpp"

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
	
	void indexDirectory(std::string path, ServerInstanceConfig serverConf, Response& response);
	void return404Page(Response& response, ServerInstanceConfig serverConf, std::string path);
};
