/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/10 12:53:34 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responder.hpp"

Responder::Responder() {}
Responder::Responder(Logger *logger) : _logger(logger) {}
Responder::~Responder() {}
Responder::Responder(const Responder &origin) { (void)origin; }
Responder &Responder::operator=(const Responder &origin)
{
	(void)origin;
	return *this;
}

LocationConfig *Responder::isCgiRequest(Request &request, ServerInstanceConfig &serverConf)
{
	for (size_t i = 0; i < serverConf.locations.size(); i++)
	{
		if (serverConf.locations[i].path == request.getPath())
		{
			_logger->print(DEBUG, std::string(SYS_MSG) + std::string(GREEN) + std::string(DIM), "CGI location is matching the requested one... executing the cgi script", 0);
			_logger->print(DEBUG, std::string(SYS_MSG) + std::string(GREEN) + std::string(DIM), serverConf.locations[i].cgi_pass, 0);
			return &(serverConf.locations[i]);
		}
	}
	return NULL;
}

Response Responder::getResponse(Request &request, ServerInstanceConfig &serverConf)
{
	Response response;
	std::ifstream file;
	std::string path;

	LocationConfig *location;
	location = isCgiRequest(request, serverConf);
	if (location != NULL)
	{
		if (!isMethodAllowed(request.getMethod(), location->allowedMethods))
		{
			response.code = 405;
			return response;
		}
		CgiHandler cgi(_logger);
		cgi.createResponse(response, request, *location, serverConf);
		return response;
	}

	if (!isMethodAllowed(request.getMethod(), serverConf.allowedMethods))
	{
		response.code = 405;
		return response;
	}

	if (request.getPath() == "/")
		path = serverConf.rootDirectory + "/" + serverConf.indexFile;
	else
		path = serverConf.rootDirectory + request.getPath();

	if (path.back() == '/')
	{
		if (serverConf.autoindex)
			indexDirectory(path, response);
		else
			response.code = 403;

		return response;
	}

	file.open(path.c_str());

	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		response.body = ss.str();
		_logger->print(INFO, GREEN, "We returned the " + path + " file", 0);
		file.close();
	}
	else
		response.code = 404;
	return response;
}

void Responder::indexDirectory(std::string path, Response &response)
{
	DIR *directory = opendir(path.c_str());

	if (directory)
	{
		struct dirent *entry;

		response.body = "<html>"
						"<head>"
						"<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">"
						"</head>"
						"<table>";

		response.body += "<th>Name</th>";
		response.body += "<th>Size</th>";

		while ((entry = readdir(directory)))
		{
			response.body += "<tr>";

			if (entry->d_type == DT_REG)
				response.body += "<td><i class=\"fa fa-file\" style=\"color:lightblue\"></i> <a href=\"" + std::string(entry->d_name) + "\">";
			else
				response.body += "<td><i class=\"fa fa-folder\" style=\"color:blue\"></i> <a href=\"" + std::string(entry->d_name) + "/\">";

			response.body += entry->d_name;
			response.body += "</a></td>";

			struct stat fileInfo;
			std::string fullPath = path + "/" + std::string(entry->d_name);

			if (stat(fullPath.c_str(), &fileInfo) == 0 && S_ISREG(fileInfo.st_mode))
				response.body += "<td>" + std::to_string(fileInfo.st_size) + " bytes</td>";
			else
				response.body += "<td></td>";

			response.body += "</tr>";
		}

		closedir(directory);
		response.body += "</table>";
	}
	else
		response.code = 404;
}

bool Responder::isMethodAllowed(const std::string& method, const std::vector<std::string>& allowedMethods)
{
	for (std::vector<std::string>::const_iterator it = allowedMethods.begin(); it != allowedMethods.end(); ++it)
	{
		if (method == *it)
			return true;
	}
	return false;
}
