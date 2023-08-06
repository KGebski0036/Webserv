/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:31:56 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/06 20:57:08 by cjackows         ###   ########.fr       */
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
	std::string path;
	
	if (request.getPath() == "/")
		path = serverConf.rootDirectory + "/" + serverConf.indexFile;
	else
		path = serverConf.rootDirectory + request.getPath();
		
	if (path.back() == '/')
	{
		if (serverConf.autoindex)
			indexDirectory(path, serverConf, response);
		else
		{
			response.code = 403;
			response.body = ErrorPages::generateErrorPage(403);
		}

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
		return404Page(response, serverConf, path);
	return response;
}

void Responder::indexDirectory(std::string path, ServerInstanceConfig serverConf, Response& response)
{
	DIR *directory = opendir(path.c_str());
	

    if (directory) {
        struct dirent *entry;

        response.body = "<html>"
                        "<head>"
                        "<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">"
                        "</head>"
                        "<table>";

        response.body += "<th>Name</th>";
        response.body += "<th>Size</th>";

        while ((entry = readdir(directory))) {
            response.body += "<tr>";

            if (entry->d_type == DT_REG) {
                response.body += "<td><i class=\"fa fa-file\" style=\"color:lightblue\"></i> <a href=\"" + std::string(entry->d_name) + "\">";
            } else {
                response.body += "<td><i class=\"fa fa-folder\" style=\"color:blue\"></i> <a href=\"" + std::string(entry->d_name) + "/\">";
            }

            response.body += entry->d_name;
            response.body += "</a></td>";

            struct stat fileInfo;
            std::string fullPath = path + "/" + std::string(entry->d_name);

            if (stat(fullPath.c_str(), &fileInfo) == 0 && S_ISREG(fileInfo.st_mode)) {
                response.body += "<td>" + std::to_string(fileInfo.st_size) + " bytes</td>";
            } else {
                response.body += "<td></td>"; // Empty cell for non-regular files
            }

            response.body += "</tr>";
        }

        closedir(directory);
        response.body += "</table>";
    }
	else
		return404Page(response, serverConf, path);
		
}

void Responder::return404Page(Response& response, ServerInstanceConfig serverConf, std::string path)
{
	std::ifstream file;
	
	response.code = 404;
	file.open(serverConf.rootDirectory + "/default_error_pages/404.html");
	_logger->print(INFO, RED, "We returned the 404 page file insted of " + path, 0);
	if (file.is_open())
	{
		getline(file, response.body, '\0');
		file.close();
	}
	else
		response.body = ErrorPages::generateErrorPage(404);
}
