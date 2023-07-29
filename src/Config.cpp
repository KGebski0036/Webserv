/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:31:33 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 15:10:13 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config* Config::readConfig(std::string &pathToFile)
{
	Config *result = new Config();
	result->readFile(pathToFile);
	//TODO Parsing
	return result;
}

void Config::readFile(std::string pathToFile)
{
	std::ifstream file;
	file.open(pathToFile.c_str());
	if (!file.is_open())
		throw MyException("Could not open a config file", __func__, __FILE__, __LINE__);

	for (size_t i = 0; getline(file, _fileVector[i]) > 0; i++)
	{
		if (_fileVector[i].empty())
			i--;
	}
	if (_fileVector.empty())
		throw MyException("File is empty...", __func__, __FILE__, __LINE__);
	for (size_t i = 0; i < _fileVector.size(); i++)
	{
		std::cout << SYS_MSG << BLUE << _fileVector[i] << E;
	}
}

Config::Config()
{

}

Config::~Config()
{

}

Config::Config(const Config&)
{

}

Config&	Config::operator=(Config const &)
{

}
