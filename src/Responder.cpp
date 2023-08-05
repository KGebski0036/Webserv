/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 16:22:32 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

Responder::Responder() {}
Responder::Responder(Logger* logger) : _logger(logger){}
Responder::~Responder() {}
Responder::Responder(const Responder &origin) { (void)origin; }
Responder& Responder::operator=(const Responder &origin) { (void)origin; return *this; }

std::string Responder::getResponse(Request& request, ServerInstanceConfig serverConf)
{
	std::string tmp;
	std::ifstream file;
	
	std::cout << YELLOW << "|" << request.path << "|" << E;

	if (request.path == "/")
	{
		file.open((serverConf.rootDirectory + "/" + serverConf.indexFile).c_str());
		_logger->print(INFO, GREEN, "We return the " + serverConf.rootDirectory + "/" + serverConf.indexFile + " file", 0);
	}
	else
	{
		file.open((serverConf.rootDirectory + request.path).c_str());
		_logger->print(INFO, GREEN, "We return the " + serverConf.rootDirectory + request.path + " file", 0);
	}

	if (file.is_open())
	{
		getline(file, tmp, '\0');
		file.close();
	}
	else
	{
		file.open(serverConf.rootDirectory + "/default_error_pages/404.html");
		if (file.is_open())
		{
			getline(file, tmp, '\0');
			file.close();
		}
		else
			tmp = ErrorPages::generateErrorPage(404);
	}
	return tmp;
}
