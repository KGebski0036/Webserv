/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/08 15:26:21 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

void CgiHandler::createResponse(Response& response, Request& request, LocationConfig& location, ServerInstanceConfig& config)
{
	(void)config;
	_logger->print(INFO, std::string(SYS_MSG) +  std::string(GREEN) +  std::string(DIM), "Building response...", 0);
	setupEnvVars(request);
	response.body = execute(location.root + "/" + location.cgi_pass);
}

std::string CgiHandler::execute(const std::string scriptPath)
{
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
		argv[0] = const_cast<char*>(scriptPath.c_str());
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
	_logger->print(INFO, std::string(SYS_MSG) +  std::string(GREEN) +  std::string(DIM), "Setting up env vars...", 0);
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
