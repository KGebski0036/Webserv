/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:17:56 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/01 16:18:53 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ErrorPages.hpp"

/**
 * RFC7231
 * https://datatracker.ietf.org/doc/html/rfc7231#section-6.2
*/
std::string ErrorPages::getHttpStatusMessage(int errorCode) {
    std::map<int, std::string> httpStatusMessages;

    // httpStatusMessages[100] = "100 Continue";
    // httpStatusMessages[101] = "101 Switching Protocols";
    
    httpStatusMessages[200] = "200 OK";
    // httpStatusMessages[201] = "201 Created";
    // httpStatusMessages[202] = "202 Accepted";
    // httpStatusMessages[203] = "203 Non-Authoritative Information";
    // httpStatusMessages[204] = "204 No Content";
    // httpStatusMessages[205] = "205 Reset Content";
    
    // httpStatusMessages[300] = "300 Multiple Choices";
    // httpStatusMessages[301] = "301 Moved Permanently";
    // httpStatusMessages[302] = "302 Found";
    // httpStatusMessages[303] = "303 See Other";
    // httpStatusMessages[305] = "305 Use Proxy";
    // httpStatusMessages[307] = "307 Temporary Redirect";

    // httpStatusMessages[400] = "400 Bad Request";
    // httpStatusMessages[402] = "402 Payment Required";
    // httpStatusMessages[403] = "403 Forbidden";
    httpStatusMessages[404] = "404 Not Found";
    // httpStatusMessages[405] = "405 Method Not Allowed";
    // httpStatusMessages[406] = "406 Not Acceptable";
    // httpStatusMessages[408] = "408 Request Timeout";
    // httpStatusMessages[409] = "409 Conflict";
    // httpStatusMessages[410] = "410 Gone";
    // httpStatusMessages[411] = "411 Length Required";
    // httpStatusMessages[413] = "413 Payload Too Large";
    // httpStatusMessages[414] = "414 URI Too Long";
    // httpStatusMessages[415] = "415 Unsupported Media Type";
    // httpStatusMessages[417] = "417 Expectation Failed";
    // httpStatusMessages[426] = "426 Upgrade Required";
    
    // httpStatusMessages[500] = "500 Internal Server Error";
    // httpStatusMessages[501] = "501 Not Implemented";
    // httpStatusMessages[502] = "502 Bad Gateway";
    // httpStatusMessages[503] = "503 Service Unavailable";
    // httpStatusMessages[504] = "504 Gateway Timeout";
    // httpStatusMessages[505] = "505 HTTP Version Not Supported";

    std::map<int, std::string>::const_iterator it = httpStatusMessages.find(errorCode);
    if (it != httpStatusMessages.end()) {
        return it->second;
    } else {
        return "Unknown";
    }
}

std::string ErrorPages::generateErrorPage(int errorCode) {
    
    std::string errorPage;

    std::stringstream ss;
    std::string errorStr;
    ss << errorCode;
    errorStr = ss.str();

    errorPage = "<!DOCTYPE html>\n"
    "<html>\n"
    "<head>\n"
    "    <title>Error " + errorStr + "</title>\n"
    "    <style>\n"
    "        body { font-family: Arial, sans-serif; background-color: #f6f6f6; }\n"
    "        .container { text-align: center; padding: 100px; }\n"
    "        .error-code { font-size: 80px; color: #444; }\n"
    "        .error-message { font-size: 24px; color: #777; }\n"
    "    </style>\n"
    "</head>\n"
    "<body>\n"
    "    <div class=\"container\">\n"
    "        <span class=\"error-code\">" + errorStr + "</span>\n"
    "        <p class=\"error-message\">Sorry, an error occurred. Please try again later.</p>\n"
    "    </div>\n"
    "</body>\n"
    "</html>\n";

    return errorPage;
}
