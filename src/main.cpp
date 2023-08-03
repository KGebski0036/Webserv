/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 12:59:37 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"
#include "../inc/Logger.hpp"

Logger logger(DEBUG);

int	main(int ac, char *av[])
{
	Config input(ac, av, logger);
	if (!input.validateInput())
		return 1;

	Webserv server(input);

	try
	{
		server.setup();
		server.run();
	} catch (const MyException &e) { std::cerr << e.what();}
	return 0;
}
