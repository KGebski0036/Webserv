/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:32:18 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/05 16:17:58 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <sstream>
#include <map>


enum HttpMethod{
	DEFAULT,
	GET,
	POST,
	DELETE
};

class Request {
  public:
	HttpMethod method;
	std::string path;
	std::map<std::string, std::string> requestParamiters;
	std::string body;
	
	Request();
	Request(std::string);
	~Request();
	Request(const Request&);
	Request& operator=(Request const &);
	
  private:
	void setMethod(std::string line);
};

