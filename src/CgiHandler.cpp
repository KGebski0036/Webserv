/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 05:36:22 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

void CgiHandler::createResponse(Response& response, Request& request, Location& location, ServerInstanceConfig& config)
{
	(void)request;
	(void)config;
	_logger->print(INFO, GREEN, "Building response...", 0);
	_logger->print(DEBUG, DIM, location.cgi_pass , 0);
	response.body = execute("", "");
	// std::cout << response.body << E;
}

std::string CgiHandler::execute(const  std::string& scriptPath, const std::string& requestData)
{
	(void)scriptPath;
	(void)requestData;
	int pipefd[2];
	char buffer[4096];

	if (pipe(pipefd) == -1)
		_logger->print(DEBUG, "Failed to create pipe. ", 1);

	pid_t pid = fork();

	if (pid == -1) {
		_logger->print(DEBUG, "Failed to create child process. ", 1);
	}
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);

		if (execl("/home/sztorm/webserv/www/cgi-bin/test.py", "simple_cgi", NULL) == -1) {
			_logger->print(DEBUG, "Failed to execute cgi script.", 1);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		close(pipefd[1]);
		wait(NULL);

        int bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (bytesRead == -1) {
			_logger->print(DEBUG, "Failed to read from the pipe.", 1);
            return "";
        }

        buffer[bytesRead] = '\0';
        dup2(1, pipefd[0]);

		return buffer;
	}
	return "";
}


void CgiHandler::setupEnvVars()
{
//todo add env vars support
}

CgiHandler::~CgiHandler() {}

CgiHandler::CgiHandler(Logger* logger) : _logger(logger) {}
CgiHandler::CgiHandler() : _logger(NULL) {}
CgiHandler::CgiHandler(const CgiHandler& src) { (void)src;}
CgiHandler& CgiHandler::operator=(CgiHandler const& src) { (void)src; return *this; }
