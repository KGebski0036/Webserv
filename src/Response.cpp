/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:27:15 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/09 19:51:41 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response() { code = 200; }
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
		code = rhs.code;
	}
	return *this;
}

size_t Response::length()
{
	return body.length();
}
