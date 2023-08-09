/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 01:24:33 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

void CgiHandler::createResponse(Response& response, Request& request, LocationConfig& location, ServerInstanceConfig& config)
{
	(void)config;
	_logger->print(DEBUG, std::string(SYS_MSG) +  std::string(GREEN) +  std::string(DIM), "Building response...", 0);
	response.body = execute(location.root + "/" + location.cgi_pass, response, request);
}

std::string CgiHandler::execute(const std::string scriptPath, Response& response, Request& request)
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
		char** _envp = setupEnvVars(request);
		
		
		if (execve(argv[0], argv, _envp) == -1) {
			_logger->print(DEBUG, "Failed to execute cgi script.", 1);
			_exit(EXIT_FAILURE);
		}
	}
	else
	{
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(pipefd[0], &readSet);

		struct timeval timeout;
        timeout.tv_sec = 1; // Timeout in seconds
        timeout.tv_usec = 0;

		close(pipefd[1]);

        int result = select(pipefd[0] + 1, &readSet, NULL, NULL, &timeout);

        if (result == -1)
			throw MyException("Select failed", __func__, __FILE__, __LINE__);
		else if (result == 0)
		{
			_logger->print(INFO, RED, "Child process timed out.", 0);
            kill(pid, SIGKILL);
			response.code = 408;
			return "";
        }
		else if (FD_ISSET(pipefd[0], &readSet))
		{
			int r;
			wait(&r);
			if (WEXITSTATUS(r) == EXIT_FAILURE)
			{
				response.code = 500;
				return "";
			}
        }

		int bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);

		if (bytesRead == -1) {
			_logger->print(DEBUG, "Failed to read from the pipe.", 1);
			return "";
		}

		buffer[bytesRead] = '\0';

		return buffer;
	}
	response.code = 500;
	return "";
}


char** CgiHandler::setupEnvVars(Request &request)
{
	char** result = new char*[5];

	std::string contentLengthVar = "CONTENT_LENGTH=" + std::to_string(request.getContentLength());
	std::string bodyVar = "BODY=" + request.getBody();
	std::string requestMethod = "REQUEST_METHOD=" + request.getMethod();
	std::string params = "PARAMS=";
	
	for (std::map<std::string, std::string>::iterator it = request.getRequestParameters().begin(); it != request.getRequestParameters().end(); it++)
	{
		params += it->first + "=" + it->second + "&";
	}
	
	result[0] = new char[contentLengthVar.size() + 1];
	result[1] = new char[bodyVar.size() + 1];
	result[2] = new char[requestMethod.size() + 1];
	result[3] = new char[params.size() + 1];
	result[4] = NULL;

	strcpy(result[0], contentLengthVar.c_str());
	strcpy(result[1], bodyVar.c_str());
	strcpy(result[2], requestMethod.c_str());
	strcpy(result[3], params.c_str());
	
	return result;
}

CgiHandler::~CgiHandler() {}

CgiHandler::CgiHandler(Logger* logger) : _logger(logger) {}
CgiHandler::CgiHandler() : _logger(NULL) {}
CgiHandler::CgiHandler(const CgiHandler& src) { (void)src;}
CgiHandler& CgiHandler::operator=(CgiHandler const& src) { (void)src; return *this; }
