/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 17:37:38 by cjackows         ###   ########.fr       */
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
};

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt);
