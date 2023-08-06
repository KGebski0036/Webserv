/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:01:27 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 22:11:50 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/CgiHandler.hpp"

void CgiHandler::createResponse(Response& response, Request& request, Location& location, ServerInstanceConfig& config)
{
	(void)request;
	(void)location;
	(void)config;
	
	response.body = execute(location.cgi_pass, "");
	std::cout << response.body << E;
	std::cout << "Aaaa" << E;
}

std::string CgiHandler::execute(const  std::string& scriptPath, const std::string& requestData)
{
	(void)_logger;
	(void)scriptPath;
	(void)requestData;

    int pipefd[2];

    if (pipe(pipefd) == -1) {
        return "";
    }

    pid_t pid = fork();

    if (pid == -1) {
        return "";
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close read end of the pipe

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);

        // Close the original write end of the pipe (no longer needed)
        close(pipefd[1]);

        // Execute the CGI script
        execl(, NULL);

        // execl should not return if successful
        std::cerr << "execl failed." << std::endl;
        _exit(EXIT_FAILURE);
    } else {
        // Parent process
        close(pipefd[1]); // Close write end of the pipe

        std::string output;
        char buffer[4096];
        int bytesRead;
        while ((bytesRead = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
            output.append(buffer, bytesRead);
        }

        close(pipefd[0]); // Close read end of the pipe
        waitpid(pid, NULL, 0); // Wait for the child process to finish
        return output;
    }
	return 0;
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
