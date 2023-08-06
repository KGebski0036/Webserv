/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 19:02:28 by gskrasti         ###   ########.fr       */
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
size_t Request::getContentLength() const { return _contentLength; }

Request::Request(std::string rawRequest)
{
	std::stringstream ss(rawRequest);
	std::string method;
	std::string tmp;
	
	std::cout << ss.str() << std::endl;
	ss >> method >> tmp >> _protocol;
	setMethod(method);
	if (tmp.find('?') != std::string::npos)
	{
		_path = tmp.substr(0, tmp.find('?'));
		tmp = tmp.substr(tmp.find('?') + 1);
		std::string key;
		std::string value;
		while (!tmp.empty() && tmp.find('=') != std::string::npos)
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
	while (tmp != "Host:")
		ss >> tmp;
	ss >> tmp;
	if (tmp.find(':') != std::string::npos)
	{
		_host = tmp.substr(0, tmp.find(':'));
		_port = std::atoi(tmp.substr(tmp.find(':') + 1).c_str());
	}
	else
	{
		_host = tmp;
		_port = 80;
	}

	if (_method == POST)
	{
		_contentLength = 0;
		bool readingBody = false;
		std::getline(ss, tmp);

		while (std::getline(ss, tmp))
		{
			if (tmp.find("content-length:") == 0)
				_contentLength = std::atoi(tmp.substr(16).c_str());
			if (!readingBody && (tmp.empty() || tmp == "\r"))
				readingBody = true;
			else if (readingBody && !tmp.empty())
			{
				_body += tmp + "\n";
				if (_body.length() >= _contentLength)
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

std::string Request::toString()
{
	std::stringstream result;
	std::string method = "UNKNOWN";
	
	if (_method == GET)
		method = "GET";
	if (_method == POST)
		method = "POST";
	if (_method == DELETE)
		method = "POST";
	
	result << std::setw(25) << YELLOW << "Method: " << GREEN << method << std::setw(20) << YELLOW << "file: "
		MAGENTA << _path << E;
	
	if (_requestParameters.size() > 0)
		result << std::setw(25) << YELLOW << "Parameters: " << E;
	
	for (std::map<std::string, std::string>::iterator it = _requestParameters.begin(); it != _requestParameters.end(); it++)
	{
		result << std::setw(30) << BLUE << it->first << " --> " << it->second << E;
	}
	
	result << std::setw(25) << YELLOW << "Server: " << GREEN << _host << ":" << _port << E;
	
	if(_body.size() > 0)
		result << std::setw(25) << YELLOW << "Body: " << BLUE << _body << E;
	
	return result.str();
}
