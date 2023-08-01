/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 15:09:40 by kgebski          ###   ########.fr       */
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
#include "ServerInstanceConfig.hpp"

class Config : public MyException {
  public:
	static Config* readConfig(std::string pathToFile);
	
	Config();
	~Config();
	Config(const Config&);
	Config&	operator=(Config const &);

	std::vector<ServerInstanceConfig> getServersConfigs() const;

  private:
	std::vector<std::string> _fileVector;
	std::vector<ServerInstanceConfig> _serversConfigs;
  
	void readFile(std::string pathToFile);
	void setupServersConfiguration();
	bool isHttpMethod(std::string str);
	ServerInstanceConfig readSingleServer(size_t& i);
	void readListenArg(ServerInstanceConfig& config, std::string str);
	void readAllowedMethodsArg(std::vector<std::string>& vec, size_t& j);
	void readLocationArg(std::vector<ServerInstanceConfig::LocationConfig>& locations, size_t& j);
};

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt);
