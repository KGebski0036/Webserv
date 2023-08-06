/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:32:18 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 16:03:16 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <map>
#include "Colors.hpp"

enum HttpMethod{
	DEFAULT,
	GET,
	POST,
	DELETE
};

class Request {
  public:
	Request();
	Request(std::string);
	~Request();
	Request(const Request&);
	Request& operator=(Request const &);
	
	HttpMethod getMethod() const;
	std::string getPath() const;
	std::map<std::string, std::string> getRequestParameters() const;
	std::string getBody() const;
	std::string getProtocol() const;
	std::string getHost() const;
	int getPort() const;
	
  private:
	void setMethod(std::string line);

	HttpMethod _method;
	std::string _path;
	std::map<std::string, std::string>  _requestParameters;
	std::string _host;
	int _port;
	std::string _body;
	std::string _protocol;
};

