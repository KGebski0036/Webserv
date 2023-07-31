/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:31:33 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 17:12:24 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config* Config::readConfig(std::string pathToFile)
{
	Config *result = new Config();
	try {
		result->readFile(pathToFile);
		result->setupServersConfiguration();
	}
	catch (const MyException &e) { std::cerr << e.what();}
	
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
		
}

void Config::setupServersConfiguration()
{
	for(size_t i = 0; i < _fileVector.size(); i++)
	{
		if (_fileVector[i++] != "server")
			throw MyException("Corupted configuration file (server should be the main key)", __func__, __FILE__, __LINE__);
			
		ServerInstanceConfig config = readSingleServer(i);
		
		std::cout << config;
		
		_serversConfigs.push_back(config);
	}
}

ServerInstanceConfig Config::readSingleServer(size_t& i)
{
	ServerInstanceConfig config;
	int bracketsCounter = 0;
	
	for (size_t j = i; j < _fileVector.size(); j++)
	{
		
		if (_fileVector[j] == "{")
			bracketsCounter++;
		else if (_fileVector[j] == "}")
			bracketsCounter--;
		else
		{
			if (_fileVector[j] == "server_name")
			{
				config.serverName = _fileVector[++j];
			}
			if (_fileVector[j] == "listen")
			{
				int separatorPosition =  _fileVector[++j].find(':'); 
				config.listenAddress = _fileVector[j].substr(0, separatorPosition);
				config.port = atoi(_fileVector[j].substr(separatorPosition + 1).c_str());
			}
			if (_fileVector[j] == "root")
			{
				config.rootDirectory = _fileVector[++j];
			}
			if (_fileVector[j] == "index")
			{
				config.indexFile = _fileVector[++j];
			}
			if (_fileVector[j] == "allow_methods")
			{
				while (isHttpMethod(_fileVector[++j]))
				{
					config.allowedMethods.push_back(_fileVector[j]);
				}
				if (_fileVector[j] == "}")
				{
					bracketsCounter--;
				}
			}
			if (_fileVector[j] == "location")
			{
				while (_fileVector[++j] != "}") {}
				
				ServerInstanceConfig::LocationConfig location;
				
				location.root = "/";
				location.index = "index.html";
				location.path = "/";
				location.allowedMethods.push_back("GET");
				
				config.locations.push_back(location);
				j++;
			}
		}
		if (bracketsCounter == 0)
		{
			i = j;
			break;
		}
	}

	if (bracketsCounter != 0)
		throw MyException("Corupted configuration file (unclosed brackets)", __func__, __FILE__, __LINE__);
		

	return config;
}

bool Config::isHttpMethod(std::string str)
{
	return  (str == "GET" || str == "POST" || str == "PUT");
}

Config::Config() {}

Config::~Config() {}

Config::Config(const Config&) : MyException() {}

Config&	Config::operator=(Config const & other)
{
	if (this != &other)
	{
		_fileVector = other._fileVector;
	}
	
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt)
{
	static int i = 0;

	i++;
	os << DARKBLUE << i << ". " << GREEN << "Server name : " << dt.serverName << E;
	os << std::setw(20) << BLUE << "ip: " << dt.listenAddress << " at port: " << dt.port << E;
	os << std::setw(20) << BLUE << "file index is: " << dt.indexFile << E;
	os << std::setw(20) << BLUE << "root directory is: " << dt.rootDirectory << E << '\n';
	os << std::setw(20) << BLUE << "allowed methods are: " << E << std::setw(20);
	
	for (size_t i = 0; i < dt.allowedMethods.size(); i++)
	{
		os << GREEN << dt.allowedMethods[i] << " ";
	}
	os << "\n\n";
	os << std::setw(20) << BLUE << "locations are: " << E;
	
	for (size_t i = 0; i < dt.locations.size(); i++)
	{
		os << std::setw(20) << DARKBLUE << i << ". location" << E;
		os << std::setw(25) << BLUE << "path: " << dt.locations[i].path << E;
		os << std::setw(25) << BLUE << "root: " << dt.locations[i].root << E;
		os << std::setw(25) << BLUE << "index: " << dt.locations[i].index << E;
		
		os << std::setw(25) << BLUE << "methods: " << E << std::setw(25);
	
		for (size_t j = 0; j < dt.locations[i].allowedMethods.size(); j++)
		{
			os << GREEN << dt.locations[i].allowedMethods[j] << " ";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}
