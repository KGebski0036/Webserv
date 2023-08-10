/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/10 14:17:00 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Request.hpp"
#include <iostream>

Request::Request() {
	_contentLength = 0;
}
Request::~Request() {}
Request::Request(const Request& src)
{
	_method = src._method;
	_path = src._path;
	_requestParameters = src._requestParameters;
	_body = src._body;
	_host = src._host;
	_port = src._port;
	_contentLength = src._contentLength;
	_contentType = src._contentType;
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
		_contentLength = src._contentLength;
		_contentType = src._contentType;
	}
	return *this; 
}

std::string Request::getMethod() const { return _method; }
std::string Request::getPath() const { return _path; }
std::map<std::string, std::string>& Request::getRequestParameters() { return _requestParameters; }
std::string Request::getBody() const { return _body; }
std::string Request::getProtocol() const { return _protocol; }
std::string Request::getHost() const { return _host; }
int Request::getPort() const { return _port; }
size_t Request::getContentLength() const { return _contentLength; }
std::string Request::getContentType() const { return _contentType; }

Request::Request(std::string rawRequest)
{
	std::stringstream ss(rawRequest);
	std::string method;
	std::string tmp;

	ss >> method >> tmp >> _protocol;
	if (method == "GET" || method == "POST" || method == "DELETE")
		_method = method;
	else
		_method = "UNKNOWN";
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
	ss >> tmp;
	if (tmp == "Content-Type:")
		ss >> _contentType;
	else
		_contentType = "text/plain";
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

	if (_method == "POST")
	{
		_contentLength = 0;
		bool readingBody = false;
		std::getline(ss, tmp);

		while (std::getline(ss, tmp))
		{
			if (tmp.find("Content-Length:") == 0)
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
	_contentLength = _body.size();
}

std::string Request::toString()
{
	std::stringstream result;

	result << std::setw(25) << YELLOW << "Method: " << GREEN << _method << std::setw(20) << YELLOW << "file: "
		MAGENTA << _path << std::endl;
	
	if (_requestParameters.size() > 0)
		result << std::setw(25) << YELLOW << "Parameters: " << std::endl;
	
	for (std::map<std::string, std::string>::iterator it = _requestParameters.begin(); it != _requestParameters.end(); it++)
	{
		result << std::setw(30) << BLUE << it->first << " --> " << it->second << std::endl;
	}
	
	result << std::setw(25) << YELLOW << "Server: " << GREEN << _host << ":" << _port << std::endl;
	
	if (_body.size() > 0 && _body.size() < 1000)
		result << std::setw(25) << YELLOW << "Body:\n" << BLUE << _body << std::endl;
	else if (_body.size() > 0)
		result << std::setw(25) << YELLOW << "Body: " << BLUE << "[...]" << std::endl;

	result << std::setw(25) << YELLOW << "Content-length: " <<  GREEN << _contentLength << std::endl;

	result << std::setw(25) << YELLOW << "Content Type: " << BLUE << _contentType << std::endl;
	
	return result.str();
}

std::string Request::displayRequestContent() {
	std::stringstream ss;
	const int width = 25;

	ss << "\n" <<WHITE << std::setw(width) << "HttpMethod: " << BLUE << _method << "\n";
	ss << WHITE << std::setw(width) << "Path: " << BLUE << _path << "\n";
	ss << WHITE << std::setw(width) << "Request Parameters: " << "\n";
	for (std::map<std::string, std::string>::const_iterator it = _requestParameters.begin(); it != _requestParameters.end(); ++it) {
		ss << WHITE << std::setw(width + 2) << BLUE << it->first << ": " << it->second << "\n";
	}
	ss << WHITE << std::setw(width) << "Host: " << BLUE << _host << "\n";
	ss << WHITE << std::setw(width) << "Port: " << BLUE << _port << "\n";
	ss << WHITE << std::setw(width) << "Body: " << BLUE << _body << "\n";
	ss << WHITE << std::setw(width) << "Protocol: " << BLUE << _protocol << "\n";
	ss << WHITE << std::setw(width) << "Content Length: " << BLUE << _contentLength << "\n";
	ss << WHITE << std::setw(width) << "Content Type: " << BLUE << _contentType << "\n";
	return ss.str();
}
