#include "../inc/Webserv.hpp"


void Webserv::config(std::string pathToFile)
{
	_config = Config::readConfig(pathToFile);
	for (size_t i = 0; i < _config->getServersConfigs().size(); i++)
	{
		ServerInstance* server = new ServerInstance(_config->getServersConfigs()[i]);
		_servers.push_back(server);
	}
}

int	 Webserv::setup()
{
	
return 0;
}

void Webserv::run()
{

}

void Webserv::clean()
{

}

Webserv::Webserv()  {}
Webserv::~Webserv() 
{
	delete _config;
	for (size_t i = 0; i < _servers.size(); i++)
	{
		delete _servers[i];
	}
}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }
