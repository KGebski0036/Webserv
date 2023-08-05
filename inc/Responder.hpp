/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responder.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 18:28:47 by kgebski           #+#    #+#             */
/*   Updated: 2023/08/05 18:12:13 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 
#include <string>
#include <fstream>
#include <sstream>

#include "Request.hpp"
#include "Logger.hpp"
#include "ServerInstanceConfig.hpp"
#include "ErrorPages.hpp"
#include "Response.hpp"

class Responder
{
  public:
  	Responder();
	Responder(Logger* logger);
	~Responder();
	Responder(const Responder &);
	Responder& operator=(const Responder &);
	
	Response getResponse(Request& request, ServerInstanceConfig serverConf);
	
  private:
	Logger* _logger;
};
