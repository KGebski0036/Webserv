/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 13:08:35 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <pthread.h>

#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"

#include "ServerInstanceConfig.hpp"

class Webserv {
  public:
	Webserv(Config&);
	~Webserv();

	int	 setup();
	void run();
	void clean();
  private:

	
	std::vector<ServerInstanceConfig> _serversConfigs;

	int createSockets(ServerInstanceConfig instanceConfig);

	Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
};
