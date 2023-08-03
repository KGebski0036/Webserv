/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:32:18 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 18:46:57 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>

enum HttpMetrhod{
	DEFAULT,
	GET,
	POST,
	DELETE
};

class Request {
  public:
	HttpMetrhod method;
	std::string path;
	std::map<std::string, std::string>  _requestParamiters;
	std::string body;
	
	Request();
	~Request();
	Request(const Request&);
	Request& operator=(Request const &);
};
