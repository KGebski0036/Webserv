/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 16:58:40 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"
#include "../inc/Logger.hpp"

Logger logger(DEBUG);

void signalHandler(int signal);

int	main(int ac, char *av[])
{
	Config input(ac, av, &logger);
	if (!input.validateInput())
		return 1;

	Webserv server(input, &logger);
	signal(SIGINT, signalHandler);
	try
	{
		server.setup();
		server.run();
	} catch (const MyException &e) { std::cerr << e.what(); return 1;}
	return 0;
}

void signalHandler(int signal) {
	std::cout << E;
	
	if (signal == SIGINT)
		logger.print(INFO, RED, "Received SIGINT signal. Exiting now...", 0);
	else if (signal == SIGTERM)
		logger.print(INFO, RED, "Received SIGTERM signal. Exiting now...", 0);
	else
		logger.print(INFO, RED, "Received unknown signal. Exiting now...", 0);

	exit(signal);
}
