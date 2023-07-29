/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 15:45:42 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Webserv.hpp"

int	main(int ac, char *av[])
{
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
	
	Webserv server;
	try
	{
		if (ac == 1)
			server.config("default.conf");
		else
			server.config(av[1]);

	} catch (const MyException &e) { std::cerr << e.what();}
	//handle configuration
	return 0;
}