/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:17:56 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/10 13:43:26 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ErrorPages.hpp"

/**
 * RFC7231
 * https://datatracker.ietf.org/doc/html/rfc7231#section-6.2
*/
std::string ErrorPages::getHttpStatusMessage(int errorCode) {
	std::map<int, std::string> httpStatusMessages;

	httpStatusMessages[200] = "200 OK";
	httpStatusMessages[400] = "400 Bad Request";
	httpStatusMessages[403] = "403 Forbidden";
	httpStatusMessages[404] = "404 Not Found";
	httpStatusMessages[405] = "405 Method Not Allowed";
	httpStatusMessages[408] = "408 Request Timeout";
	httpStatusMessages[500] = "500 Internal Server Error";

	std::map<int, std::string>::const_iterator it = httpStatusMessages.find(errorCode);
	if (it != httpStatusMessages.end()) {
		return it->second;
	} else {
		return "Unknown";
	}
}

std::string ErrorPages::generateErrorPage(int errorCode, ServerInstanceConfig serverConf) {

	std::fstream file;
	std::string result;
	
	file.open(serverConf.rootDirectory + "/" + serverConf.errorPages[errorCode]);
	if (file.is_open())
	{
		getline(file, result, '\0');
		file.close();
		return result;
	}

	std::stringstream ss;
	std::string errorStr;
	ss << errorCode;
	errorStr = ss.str();

	result = "<!DOCTYPE html>\n"
	"<html>\n"
	"<head>\n"
	"    <title>Error " + errorStr + "</title>\n"
	"    <style>\n"
	"        body {   min-height: 100%; font-family: Arial, sans-serif; background-image: url('https://i.giphy.com/media/TqiwHbFBaZ4ti/giphy.webp');"
	"             background-repeat: no-repeat;"
    "             background-attachment: fixed;"
	"             background-size: 100% 100%;}\n"
	"        .container { text-align: center; padding: 100px; }\n"
	"        .error-code { font-size: 80px; color: #444; }\n"
	"        .error-message { font-size: 24px; color: #777; }\n"
	"         html{ height: 100%; }"
	"    </style>\n"
	"</head>\n"
	"<body>\n"
	"    <div class=\"container\">\n"
	"        <span class=\"error-code\">" + getHttpStatusMessage(errorCode) + "</span>\n"
	"        <p class=\"error-message\">Sorry, an error occurred. Please try again later.</p>\n"
	"    </div>\n"
	"</body>\n"
	"</html>\n";

	return result;
}
