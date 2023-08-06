/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 17:41:15 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

std::string CgiHandler::execute(const  std::string& scriptPath, const std::string& requestData)
{
	(void)_logger;
	(void)requestData;
	(void)scriptPath;

	int pipefd[2];

	if (pipe(pipefd) == -1)
		return "";

	pid_t pid = fork();

	if (pid == -1)
		return "";
	else if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);

		setupEnvVars();
		
		// execl(scriptPath.c_str(), scriptPath.c_str(), NULL, _envp);
		// _exit(EXIT_FAILURE);
	}
	else
	{
		close(pipefd[1]);

		std::string output;
		char buffer[4096];
		int bytesRead;
		while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0)
			output.append(buffer, bytesRead);

		close(pipefd[0]);
		waitpid(pid, NULL, 0);
		return output;
	}
	return "";
}

void CgiHandler::setupEnvVars()
{
	size_t numEnvVars = _envVars.size();
	_envp = new char*[numEnvVars + 1];

	size_t i = 0;
	for (std::map<std::string, std::string>::const_iterator it = _envVars.begin(); it != _envVars.end(); ++it) {
		std::string envVar = it->first + "=" + it->second;
		_envp[i] = new char[envVar.size() + 1];
		std::strcpy(_envp[i], envVar.c_str());
		++i;
	}
	_envp[numEnvVars] = NULL;
}

void CgiHandler::setEnvVar(const std::string& key, const std::string& value) { _envVars[key] = value; }

CgiHandler::~CgiHandler()
{
	if (_envp)
	{
		for (size_t i = 0; i < _envVars.size(); ++i)
			delete[] _envp[i];
		delete[] _envp;
	}
}

CgiHandler::CgiHandler(Logger* logger) : _logger(logger) {}
CgiHandler::CgiHandler() : _logger(NULL) {}
CgiHandler::CgiHandler(const CgiHandler& src) { (void)src;}
CgiHandler& CgiHandler::operator=(CgiHandler const& src) { (void)src; return *this; }
