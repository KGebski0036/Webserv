/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:34:21 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 15:45:03 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "Colors.hpp"
#include "MyException.hpp"
#include "Config.hpp"

class Webserv {
  public:
	Webserv();
	~Webserv();

	void config(std::string pathToFile);
	int	 setup();
	void run();
	void clean();

  private:
  	Config*	_config;
	Webserv(const Webserv&);
	Webserv& operator=(Webserv const &);
	
};
