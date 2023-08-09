/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 15:26:06 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/09 19:51:18 by cjackows         ###   ########.fr       */
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
	
	int code;
	std::string body;
};
