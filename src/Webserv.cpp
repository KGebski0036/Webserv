/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:07:57 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/02 19:58:10 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"


//needs refactoring
// void Webserv::config(std::string pathToFile)
// {
// 	_config = Config::readConfig(pathToFile);

// 	for (size_t i = 0; i < _config->getServersConfigs().size(); i++)
// 	{
// 		ServerInstance* server = new ServerInstance(_config->getServersConfigs()[i]);
// 		_servers.push_back(server);
// 	}
// }

int	 Webserv::setup()
{
	_servers[1]->setup();
	return 0;
}

void Webserv::run()
{
	_servers[1]->run();
}

void Webserv::clean()
{

}

Webserv::Webserv(Config& input) : _config(&input) {}

Webserv::~Webserv() 
{
	// for (size_t i = 0; i < _servers.size(); i++)
	// 	delete _servers[i];
}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }
