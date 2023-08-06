/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 16:11:39 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Request.hpp"
#include <iostream>

Request::Request() {}
Request::~Request() {}
Request::Request(const Request& src)
{
	_method = src._method;
	_path = src._path;
	_requestParameters = src._requestParameters;
	_body = src._body;
	_host = src._host;
	_port = src._port;
}
Request& Request::operator=(const Request& src)
{
	if(&src != this)
	{
		_method = src._method;
		_path = src._path;
		_requestParameters = src._requestParameters;
		_body = src._body;
		_host = src._host;
		_port = src._port;
	}
	return *this; 
}

HttpMethod Request::getMethod() const { return _method; }
std::string Request::getPath() const { return _path; }
std::map<std::string, std::string> Request::getRequestParameters() const { return _requestParameters; }
std::string Request::getBody() const { return _body; }
std::string Request::getProtocol() const { return _protocol; }
std::string Request::getHost() const { return _host; }
int Request::getPort() const { return _port; }

Request::Request(std::string rawRequest)
{
	std::stringstream ss(rawRequest);
	std::string method;
	std::string tmp;
	
	ss >> method >> tmp >> _protocol;
	setMethod(method);
	if (tmp.find('?') != std::string::npos)
	{
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
		}
	}
	else
		_path = tmp;
		
	ss >> tmp >> tmp;
	_host = tmp.substr(0, tmp.find(':'));
	_port = std::atoi(tmp.substr(tmp.find(':') + 1).c_str());

	if (_method == POST)
	{
		size_t contentLength = 0;
		bool readingBody = false;
		std::getline(ss, tmp);

		while (std::getline(ss, tmp))
		{
			if (tmp.find("content-length:") == 0)
				contentLength = std::atoi(tmp.substr(16).c_str());
			if (!readingBody && (tmp.empty() || tmp == "\r"))
				readingBody = true;
			else if (readingBody && !tmp.empty())
			{
				_body += tmp + "\n";
				if (_body.length() >= contentLength)
					break;
			}
		}
	}
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
