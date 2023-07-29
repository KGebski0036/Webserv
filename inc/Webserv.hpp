/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 15:07:02 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"

class Webserv {
  public:
	static Webserv* getInstance();

	void config(std::string pathToFile);
	int	 setup();
	void run();
	void clean();

  private:
  	Config*	_config;
  	static Webserv* _instance;
	Webserv();
	~Webserv();
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
	
};