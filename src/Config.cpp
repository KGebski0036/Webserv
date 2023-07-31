/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:31:33 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 14:54:13 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config* Config::readConfig(std::string pathToFile)
{
	Config *result = new Config();
	try {
		result->readFile(pathToFile);	
	}
	catch (const MyException &e) { std::cerr << e.what();}
	//TODO Parsing
	return result;
}

void Config::readFile(std::string pathToFile)
{
	std::ifstream file;
	std::string buffer;
	std::string tmp;
	std::stringstream ss;
	
	file.open(pathToFile.c_str());
	if (!file.is_open())
		throw MyException("Could not open a config file", __func__, __FILE__, __LINE__);

	getline(file, buffer, '\0');
	ss << buffer;

	while (ss >> tmp)
	{
		_fileVector.push_back(tmp);
		if (tmp.empty())
			_fileVector.pop_back();
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

Config::Config(const Config&) : MyException()
{

}

Config&	Config::operator=(Config const & other)
{
	if (this != &other)
	{
		_fileVector = other._fileVector;
	}
	
	return *this;
}
