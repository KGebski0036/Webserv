/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/05 16:55:36 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Request.hpp"
#include <iostream>

Request::Request() {}
Request::~Request() {}
Request::Request(const Request& src) { (void)src; }
Request& Request::operator=(Request const& src) { (void)src; return *this; }

HttpMethod Request::getMethod() const { return _method; }
std::string Request::getPath() const { return _path; }
std::map<std::string, std::string> Request::getRequestParameters() const { return _requestParameters; }
std::string Request::getBody() const { return _body; }
std::string Request::getProtocol() const { return _protocol; }

Request::Request(std::string rawRequest)
{
	std::stringstream ss(rawRequest);
	std::string method;
	std::string tmp;
	
	ss >> method >> tmp >> _protocol;
	setMethod(method);
	_path = tmp.substr(0, tmp.find('?'));
	tmp = tmp.substr(tmp.find('?') + 1);

	std::string key;
	std::string value;
	while (!tmp.empty())
	{
		key = tmp.substr(0, tmp.find('='));
		tmp = tmp.substr(tmp.find('=') + 1);
		size_t ampersandPos = tmp.find('&');
		size_t spacePos = tmp.find(' ');
		if (ampersandPos < spacePos)
		{
			value = tmp.substr(0, ampersandPos);
			tmp = tmp.substr(ampersandPos + 1);
		}
		else
		{
			value = tmp.substr(0, spacePos);
			tmp = tmp.substr(spacePos + 1);
		}
		_requestParameters[key] = value;
		// std::cout << "Key: " << key << " Value: " << value << std::endl;
	}
	// while (std::getline(ss, tmp))
	// {
	// 	if (tmp.empty())
	// 		break;
	// 	// std::cout << tmp << std::endl;
	// }
}

void Request::setMethod(std::string line)
{
	if (line == "GET")
		_method = GET;
	else if (line == "POST")
		_method = POST;
	else if (line == "DELETE")
		_method = DELETE;
	else
		_method = DEFAULT;
}
