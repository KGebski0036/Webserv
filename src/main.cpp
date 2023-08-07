/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 03:12:35 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Logger.hpp"
#include "../inc/Webserv.hpp"
#include "../inc/CgiHandler.hpp"

Logger logger(DEBUG);

/*
* Execute CGI based on certain file extension (for example .php).
	* Because you won’t call the CGI directly, use the full path as PATH_INFO.

	* Just remember that, for chunked request, your server needs to unchunk
	*  it, the CGI will expect EOF as end of the body.

	* Same things for the output of the CGI. If no content_length is returned
	* from the CGI, EOF will mark the end of the returned data.

	* Your program should call the CGI with the file requested as first argument.
	* The CGI should be run in the correct directory for relative path file access.
	* Your server should work with one CGI (php-CGI, Python, and so forth).
*/

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
