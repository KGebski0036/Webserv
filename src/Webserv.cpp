#include "../inc/Webserv.hpp"


void Webserv::config(std::string pathToFile)
{
	_config = Config::readConfig(pathToFile);
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
}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }