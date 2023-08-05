/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:27:15 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 16:21:36 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() { cgiState = 0; code = 200; }
Response::~Response() {}
Response::Response(const Response& rhs)
{ 
	*this = rhs;
}
Response& Response::operator=(const Response& rhs)
{
	if (&rhs != this)
	{
		body = rhs.body;
		cgiState = rhs.cgiState;
		code = rhs.code;
	}
	return *this;
}

size_t Response::length()
{
	return body.length();
}
