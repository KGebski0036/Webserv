/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/02 19:52:40 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <pthread.h>

#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"

#include "ServerInstance.hpp"

class Webserv {
  public:
	Webserv(Config&);
	~Webserv();

	void config(std::string pathToFile);
	int	 setup();
	void run();
	void clean();
  private:
  	Config*	_config;
	std::vector<ServerInstance *> _servers;
	std::vector<pthread_t *> _serverThreads;
	Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
};
