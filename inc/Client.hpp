/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:49:26 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 18:35:15 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Request.hpp"

class Client {
  public:
	Client();
	Client(int);
	~Client();
	Client& operator=(Client const &);

  private:
	Request request;
	int _clientSocket;
	Client(const Client&);
};
