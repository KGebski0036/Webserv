/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:49:26 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 01:02:18 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include "Response.hpp"
#include "ServerInstanceConfig.hpp"

class Client {
  public:
	Client();
	Client(int);
	~Client();
	Client& operator=(Client const &);
	Request request;
	Response response;
	ServerInstanceConfig server;

  private:
	int _clientSocket;
	//time
	Client(const Client&);
};
