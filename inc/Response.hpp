/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:26:06 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 15:39:08 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

class Response
{
  public:
	Response();
	~Response();
	Response(const Response&);
	Response& operator=(const Response&);
	size_t length();
	
	std::string body;
	int cgiState;
	int code;
};
