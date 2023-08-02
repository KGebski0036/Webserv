/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:31:33 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 17:25:01 by kgebski          ###   ########.fr       */
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
				config.serverName = _fileVector[++j];
			else if (_fileVector[j] == "root")
				config.rootDirectory = _fileVector[++j];
			else if (_fileVector[j] == "index")
				config.indexFile = _fileVector[++j];
			else if (_fileVector[j] == "client_body_buffer_size")
				config.clientBodyBufferSize = atoi(_fileVector[++j].c_str());
			else if (_fileVector[j] == "autoindex")
				config.autoindex = _fileVector[++j] == "on";
			else if (_fileVector[j] == "listen")
				readListenArg(config, _fileVector[++j]);
			else if (_fileVector[j] == "allow_methods")
				readAllowedMethodsArg(config.allowedMethods, j);
			else if (_fileVector[j] == "location")
				readLocationArg(config.locations, j);
			else if (_fileVector[j] == "error_page")
				readErrorPageArg(config.errorPages, j);
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

std::vector<ServerInstanceConfig> Config::getServersConfigs() const { return _serversConfigs; }

Config::Config() {}

Config::~Config() 
{
}

Config::Config(const Config&) : MyException() {}

Config&	Config::operator=(Config const & other)
{
	if (this != &other)
		_fileVector = other._fileVector;
	
	return *this;
}

void Config::readErrorPageArg(std::map<int, std::string>& map, size_t& j)
{
	j++;
	map[atoi(_fileVector[j].c_str())] = _fileVector[j + 1];
	j++;
}

void Config::readListenArg(ServerInstanceConfig& config, std::string str)
{
	int separatorPosition =  str.find(':'); 
	config.listenAddress = str.substr(0, separatorPosition);
	config.port = atoi(str.substr(separatorPosition + 1).c_str());
}

void Config::readAllowedMethodsArg(std::vector<std::string>& vec, size_t& j)
{
	while (isHttpMethod(_fileVector[j]))
		vec.push_back(_fileVector[j++]);
}

void Config::readLocationArg(std::vector<ServerInstanceConfig::LocationConfig>& locations, size_t& j)
{
	ServerInstanceConfig::LocationConfig location;
	int bracketsCounter = 1;
	
	location.path = _fileVector[++j];
	
	if (_fileVector[++j] != "{")
		throw MyException("Corupted configuration file (unclosed brackets)", __func__, __FILE__, __LINE__);
	
	while (j < _fileVector.size() && bracketsCounter != 0)
	{
		j++;
		if (_fileVector[j] == "{")
			bracketsCounter++;
		else if (_fileVector[j] == "}")
			bracketsCounter--;
		else if (_fileVector[j] == "root")
			location.root = _fileVector[++j];
		else if (_fileVector[j] == "index")
			location.index = _fileVector[++j];
		else if (_fileVector[j] == "client_body_buffer_size")
			location.clientBodyBufferSize = atoi(_fileVector[++j].c_str());
		else if (_fileVector[j] == "cgi_pass")
			location.cgi_pass = _fileVector[++j];
		else if (_fileVector[j] == "allow_methods")
		{
			readAllowedMethodsArg(location.allowedMethods, ++j);
			j--;
		}
		else if (_fileVector[j] == "location")
		{
			location.nestedLocation = nestedLocation(j);
		}
	}
	j++;
	locations.push_back(location);
}


std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt)
{
	static int i = 0;

	i++;
	os << DARKBLUE << i << ". " << GREEN << "Server name : " << dt.serverName;
	os << std::setw(20) << BLUE << "autoindex : " << (dt.autoindex ? "on" : "off") << E;
	os << std::setw(20) << BLUE << "ip:    " << MAGENTA << dt.listenAddress << ":" << dt.port << E;
	os << std::setw(20) << BLUE << "index: " << DARKBLUE << dt.indexFile;
	os << std::setw(20) << BLUE << "root: " << DARKBLUE << dt.rootDirectory << E << '\n';
	os << std::setw(20) << BLUE << "allowed methods are: " << std::setw(10);
	
	for (size_t i = 0; i < dt.allowedMethods.size(); i++)
	{
		os << GREEN << dt.allowedMethods[i] << " ";
	}
	os << "\n\n";
	os << std::setw(20) << BLUE << "ErrorPages: " << E;
	
	for (std::map<int, std::string>::const_iterator it = dt.errorPages.begin(); it != dt.errorPages.end(); it++)
	{
		std::cout << std::setw(25) << RED << it->first << " - " << DARKBLUE << it->second << E;
	}
	
	os << std::setw(20) << BLUE << "locations are: " << E;
	
	for (size_t i = 0; i < dt.locations.size(); i++)
	{
		os << std::setw(20) << DARKBLUE << i << ". location" << E;
		os << std::setw(25) << BLUE << "path: " << DARKBLUE << dt.locations[i].path;
		os << std::setw(10) << BLUE << " root: " << DARKBLUE << dt.locations[i].root;
		os << std::setw(10) << BLUE << " cgi pass: " << DARKBLUE << dt.locations[i].cgi_pass;
		os << std::setw(10) << BLUE << " index: " << DARKBLUE << dt.locations[i].index << E;
		
		os << std::setw(25) << BLUE << "methods: " << std::setw(10);
	
		for (size_t j = 0; j < dt.locations[i].allowedMethods.size(); j++)
		{
			os << GREEN << dt.locations[i].allowedMethods[j] << " ";
		}
		os << "\n";
	}
	os << "\n";
	return os;
}
