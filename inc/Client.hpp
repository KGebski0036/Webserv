/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:49:26 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/05 15:30:21 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"
#include "Response.hpp"

class Client {
  public:
	Client();
	Client(int);
	~Client();
	Client& operator=(Client const &);
	Request request;
	Response response;

  private:
	int _clientSocket;
	Client(const Client&);
};
