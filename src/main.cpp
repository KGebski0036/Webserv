/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 13:00:25 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

int	main(int ac, char *av[])
{
	(void)av;
	if (ac == 1)
	{
		std::cout << INFO << "Default configuration used." << E;
	}
	else if (ac > 2)
	{
		std::cout << ERROR << "Wrong parameters passed to the program." << E;
		std::cout << SYS_MSG << RED << "Usage: ./webserv <path to cofiguration file> " << E;
		return 1;
	}
	
	Webserv* server = Webserv::getInstance();
	//handle configuration
	(void)server;
	return 0;
}