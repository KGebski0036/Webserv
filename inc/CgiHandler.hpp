/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGIHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:00:06 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/06 16:42:52 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "Logger.hpp"

class CgiHandler {
  public:
	CgiHandler(Logger *);
	~CgiHandler();

    std::string execute(const std::string& scriptPath, const std::string& requestData);

	void setEnvVar(const std::string& key, const std::string& value);

  private:
	char** _envp;
	std::map<std::string, std::string> _envVars;
	Logger* _logger;

	void setupEnvVars();

	CgiHandler();
	CgiHandler(const CgiHandler&);
	CgiHandler& operator=(CgiHandler const&);
};
