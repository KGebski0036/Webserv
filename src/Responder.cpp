/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 18:13:17 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

Responder::Responder() {}
Responder::Responder(Logger* logger) : _logger(logger){}
Responder::~Responder() {}
Responder::Responder(const Responder &origin) { (void)origin; }
Responder& Responder::operator=(const Responder &origin) { (void)origin; return *this; }

Response Responder::getResponse(Request& request, ServerInstanceConfig serverConf)
{
	Response response;
	std::ifstream file;
	
	if (request.getPath() == "/")
		file.open((serverConf.rootDirectory + "/" + serverConf.indexFile).c_str());
	else
		file.open((serverConf.rootDirectory + request.getPath()).c_str());

	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		response.body = ss.str();
		_logger->print(INFO, GREEN, "We returned the " + serverConf.rootDirectory + request.getPath() + " file", 0);
		file.close();
	}
	else
	{
		response.code = 404;
		file.open(serverConf.rootDirectory + "/default_error_pages/404.html");
		_logger->print(INFO, RED, "We returned the 404 page file", 0);
		if (file.is_open())
		{
			getline(file, response.body, '\0');
			file.close();
		}
		else
			response.body = ErrorPages::generateErrorPage(404);
	}
	return response;
}
