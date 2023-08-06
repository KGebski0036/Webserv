/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 12:32:00 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 16:45:54 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Webserv.hpp"
#include "../inc/Logger.hpp"
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
int	main(int ac, char *av[])
{
	Config input(ac, av, &logger);
	if (!input.validateInput())
		return 1;

	Webserv server(input, &logger);

	try
	{
		server.setup();
		server.run();
	} catch (const MyException &e) { std::cerr << e.what(); return 1;}
	return 0;
}
