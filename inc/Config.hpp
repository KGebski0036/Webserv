/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 16:09:06 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>

#include "Colors.hpp"
#include "MyException.hpp"
#include "Logger.hpp"
#include "ServerInstanceConfig.hpp"

#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <poll.h>
#include <fcntl.h>

#include "ErrorPages.hpp"
#include "MIMEtypes.hpp"

class Config : public MyException {
  public:
	Config(int ac, char* av[], Logger& logger);
	~Config();

	bool validateInput();
	std::vector<ServerInstanceConfig> getServersConfigs() const;

  private:
  	int _ac;
	char **_av;
	Logger* _logger;
	std::vector<std::string> _fileVector;
	std::vector<ServerInstanceConfig> _serversConfigs;
  
	void readFile(std::string pathToFile);
	void setupServersConfiguration();

	ServerInstanceConfig readSingleServer(size_t& i);

	bool isHttpMethod(std::string str);
	void readListenArg(ServerInstanceConfig& config, std::string str);
	void readAllowedMethodsArg(std::vector<std::string>& vec, size_t& j);
	void readErrorPageArg(std::map<int, std::string>& map, size_t& j);
	void readLocationArg(std::vector<ServerInstanceConfig::LocationConfig>& locations, size_t& j);
	ServerInstanceConfig::LocationConfig* nestedLocation(size_t& j);

	Config();
	Config(const Config&);
	Config&	operator=(Config const &);
};

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt);
