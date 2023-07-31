/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 15:44:27 by kgebski          ###   ########.fr       */
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

  private:
	std::vector<std::string> _fileVector;
	std::vector<ServerInstanceConfig> _serversConfigs;
  
	void readFile(std::string pathToFile);
	void setupServersConfiguration();
	bool isHttpMethod(std::string str);
	ServerInstanceConfig readSingleServer(size_t& i);
};

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt);
