/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 14:43:15 by kgebski          ###   ########.fr       */
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
	(void)_logger;
	std::string tmp;
	std::ifstream file;
	
	if (request.path == "/")
	{
		file.open((serverConf.rootDirectory + serverConf.indexFile).c_str());
		std::cout << MAGENTA << "We return the " << serverConf.rootDirectory + "/" + serverConf.indexFile << " file" << E;
	}
	else
	{
		file.open((serverConf.rootDirectory + request.path).c_str());
		std::cout << GREEN << "We return the " << serverConf.rootDirectory + request.path << " file" << E;
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
