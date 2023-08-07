/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 20:29:59 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

void CgiHandler::createResponse(Response& response, Request& request, Location& location, ServerInstanceConfig& config)
{
	(void)request;
	(void)config;
	(void)location;
	_logger->print(INFO, GREEN, "Building response...", 0);
	// _logger->print(DEBUG, DIM, location.path, 0); //! Data is lost, can't process the cgi location
	setupEnvVars(request);
	response.body = execute("", "");
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
		char *argv[2];
		argv[0] = "www/cgi-bin/userPanel.py";
		argv[1] = NULL;
		
		if (execve(argv[0], argv, _envp) == -1) {
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


void CgiHandler::setupEnvVars(Request &request)
{
	std::cout << YELLOW << request.getContentLength() << E;
	std::string contentLengthVar = "CONTENT_LENGTH=" + std::to_string(request.getContentLength());
	std::string bodyVar = "BODY=" + request.getBody();
	std::string requestMethod = "REQUEST_METHOD=POST"; //! Change it!!!!!!!!
	_envp[0] = const_cast<char*>(contentLengthVar.c_str());
    _envp[1] = const_cast<char*>(bodyVar.c_str());
	_envp[2] = const_cast<char*>(requestMethod.c_str());
    _envp[3] = NULL;
}

CgiHandler::~CgiHandler() {}

CgiHandler::CgiHandler(Logger* logger) : _logger(logger) {}
CgiHandler::CgiHandler() : _logger(NULL) {}
CgiHandler::CgiHandler(const CgiHandler& src) { (void)src;}
CgiHandler& CgiHandler::operator=(CgiHandler const& src) { (void)src; return *this; }
