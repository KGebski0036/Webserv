/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:31:33 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 18:55:34 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Config.hpp"

Config::Config(int ac, char* av[], Logger* logger) : _ac(ac), _av(av), _logger(logger) {}

bool Config::validateInput() {
	try {
		if (_ac == 1) {
			_logger->print(INFO, C_INFO, "Default webserv configuration used.", false);
			readFile("default.conf");
		}
		else if (_ac > 2) {
			_logger->print(INFO, C_ERROR, "Wrong parameters passed to the program.", true);
			return false;
		}
		else
			readFile(_av[1]);
	setupServersConfiguration();
	}
	catch (const MyException &e) { std::cerr << e.what(); return false;}
	return true;
}

void Config::readFile(std::string pathToFile) {
	std::ifstream file;
	std::string buffer;
	std::string tmp;
	std::stringstream ss;
	
	file.open(pathToFile.c_str());
	if (!file.is_open())
		throw MyException("Could not open a config file", __func__, __FILE__, __LINE__);

	getline(file, buffer, '\0');
	file.close();
	ss << buffer;

	while (ss >> tmp) {
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
		throw MyException("Corupted configuration file (unclosed brackets)", __func__, __FILE__, __LINE__); //!
	
	return config;
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

bool Config::isHttpMethod(std::string str) { return  (str == "GET" || str == "POST" || str == "PUT"); }

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
		// else if (_fileVector[j] == "location")
		// {
		// 	location.nestedLocation = nestedLocation(j);
		// }
	}
	j++;
	locations.push_back(location);
}

void Config::readErrorPageArg(std::map<int, std::string>& map, size_t& j)
{
	j++;
	map[atoi(_fileVector[j].c_str())] = _fileVector[j + 1];
	j++;
}

ServerInstanceConfig::LocationConfig* Config::nestedLocation(size_t& j)
{
	std::cout << MAGENTA << _fileVector[j] << E;
	ServerInstanceConfig::LocationConfig* location = new ServerInstanceConfig::LocationConfig(); //TODO This has to be freed
	int bracketsCounter = 1;
	
	location->path = _fileVector[++j];
	
	// if (_fileVector[++j] != "{")
	// 	throw MyException("Corupted configuration file (unclosed brackets)", __func__, __FILE__, __LINE__);
	
	while (j < _fileVector.size() && bracketsCounter != 0)
	{
		j++;
		if (_fileVector[j] == "{")
			bracketsCounter++;
		else if (_fileVector[j] == "}")
			bracketsCounter--;
	// 	else if (_fileVector[j] == "root")
	// 		location->root = _fileVector[++j];
	// 	else if (_fileVector[j] == "index")
	// 		location->index = _fileVector[++j];
	// 	else if (_fileVector[j] == "client_body_buffer_size")
	// 		location->clientBodyBufferSize = atoi(_fileVector[++j].c_str());
	// 	else if (_fileVector[j] == "cgi_pass")
	// 		location->cgi_pass = _fileVector[++j];
	// 	else if (_fileVector[j] == "allow_methods")
	// 	{
	// 		readAllowedMethodsArg(location->allowedMethods, ++j);
	// 		j--;
	// 	}
	// 	else if (_fileVector[j] == "location")
	// 	{
	// 		location->nestedLocation = nestedLocation(j);
	// 	}
	}
	j++;
	return location;
}

std::vector<ServerInstanceConfig> Config::getServersConfigs() const { return _serversConfigs; }

Config::Config() {}

Config::~Config() {}

Config::Config(const Config&) : MyException() {}

Config&	Config::operator=(Config const & other)
{
	if (this != &other)
		_fileVector = other._fileVector;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ServerInstanceConfig& dt)
{
	static int i = 0;

	i++;
	os << DARKBLUE << i << ". " << GREEN << "Server name : " << dt.serverName;
	os << std::setw(30) << BLUE << "autoindex : " << (dt.autoindex ? "on" : "off") << std::endl;
	os << std::setw(30) << BLUE << "ip:    " << MAGENTA << dt.listenAddress << ":" << dt.port << std::endl;
	os << std::setw(30) << BLUE << "index: " << DARKBLUE << dt.indexFile;
	os << std::setw(30) << BLUE << "root: " << DARKBLUE << dt.rootDirectory << std::endl << '\n';
	os << std::setw(30) << BLUE << "allowed methods are: " << std::setw(10);
	
	for (size_t i = 0; i < dt.allowedMethods.size(); i++)
	{
		os << GREEN << dt.allowedMethods[i] << " ";
	}
	os << "\n\n";
	os << std::setw(30) << BLUE << "ErrorPages: " << std::endl;
	
	// for (std::map<int, std::string>::const_iterator it = dt.errorPages.begin(); it != dt.errorPages.end(); it++)
	// {
	// 	std::cout << std::setw(35) << RED << it->first << " - " << DARKBLUE << it->second << std::endl;
	// }
	
	os << std::setw(30) << BLUE << "locations are: " << std::endl;
	
	for (size_t i = 0; i < dt.locations.size(); i++)
	{
		os << std::setw(30) << DARKBLUE << i << ". location" << std::endl;
		os << std::setw(35) << BLUE << "path: " << DARKBLUE << dt.locations[i].path;
		os << std::setw(20) << BLUE << " root: " << DARKBLUE << dt.locations[i].root;
		os << std::setw(20) << BLUE << " cgi pass: " << DARKBLUE << dt.locations[i].cgi_pass;
		os << std::setw(20) << BLUE << " index: " << DARKBLUE << dt.locations[i].index << std::endl;
		
		os << std::setw(35) << BLUE << "methods: " << std::setw(10);
	
		for (size_t j = 0; j < dt.locations[i].allowedMethods.size(); j++)
		{
			os << GREEN << dt.locations[i].allowedMethods[j] << " ";
		}
		os << std::endl;
	}
	os << std::endl;
	return os;
}
