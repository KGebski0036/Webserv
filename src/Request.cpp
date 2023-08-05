/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/04 18:14:43 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Request.hpp"

Request::Request() {}
Request::~Request() {}
Request::Request(const Request& src) { (void)src; }
Request& Request::operator=(Request const& src) { (void)src; return *this; }

Request::Request(std::string raw_request)
{
	std::stringstream ss;
	std::string tmp;
	
	ss << raw_request;
	
	ss >> tmp;
	setMethod(tmp);
	
	ss >> tmp;
	path = tmp.substr(0, tmp.find('?'));
	
	tmp = tmp.substr(tmp.find('?') + 1);
	//TODO tmp is haveing a request parameters inside. We have to separate them and add to _requestParamiters
	
	
}

void Request::setMethod(std::string line)
{
	if (line == "GET")
		method = GET;
	else if (line == "POST")
		method = POST;
	else if (line == "DELETE")
		method = DELETE;
	else
		method = DEFAULT;
}
