/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 17:08:00 by gskrasti         ###   ########.fr       */
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
	
	if (request.getPath() == "/")
		file.open((serverConf.rootDirectory + serverConf.indexFile).c_str());
	else
		file.open((serverConf.rootDirectory + request.getPath()).c_str());

	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		tmp = ss.str();
		_logger->print(INFO, GREEN, "We returned the " + serverConf.rootDirectory + request.getPath() + " file", 0);
		file.close();
	}
	else
	{
		file.open(serverConf.rootDirectory + "/default_error_pages/404.html");
		_logger->print(INFO, RED, "We returned the 404 page file", 0);
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
