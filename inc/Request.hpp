/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:32:18 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/08 20:05:21 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <map>
#include <iomanip>
#include <iostream>

#include "Colors.hpp"

class Request {
  public:
	Request();
	Request(std::string);
	~Request();
	Request(const Request&);
	Request& operator=(Request const &);
	
	std::string getMethod() const;
	std::string getPath() const;
	std::map<std::string, std::string>& getRequestParameters();
	std::string getBody() const;
	std::string getProtocol() const;
	std::string getHost() const;
	int getPort() const;
	size_t getContentLength() const;
	std::string getContentType() const;
	
	std::string toString();
	std::string displayRequestContent();

  private:
	std::string _method;
	std::string _path;
	std::map<std::string, std::string>  _requestParameters;
	std::string _host;
	int _port;
	std::string _body;
	std::string _protocol;
	size_t _contentLength;
	std::string _contentType;
};

