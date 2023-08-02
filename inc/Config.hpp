/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/02 20:03:39 by cjackows         ###   ########.fr       */
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

class Config : public MyException {
  public:
	// static Config* readConfig(std::string pathToFile);

	bool validateInput();
	void readFile(std::string pathToFile);

	Config(int ac, char* av[], Logger& logger);
	Config();
	~Config();
	Config(const Config&);
	Config&	operator=(Config const &);

	std::vector<ServerInstanceConfig> getServersConfigs() const;

  private:
  	int _ac;
	char **_av;
	Logger* _logger;
	std::vector<std::string> _fileVector;
	std::vector<ServerInstanceConfig> _serversConfigs;
  
	void setupServersConfiguration();
	bool isHttpMethod(std::string str);
	ServerInstanceConfig readSingleServer(size_t& i);
	void readListenArg(ServerInstanceConfig& config, std::string str);
	void readAllowedMethodsArg(std::vector<std::string>& vec, size_t& j);
	void readLocationArg(std::vector<ServerInstanceConfig::LocationConfig>& locations, size_t& j);
	void readErrorPageArg(std::map<int, std::string>& map, size_t& j);
	ServerInstanceConfig::LocationConfig* nestedLocation(size_t& j);
};

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt);
