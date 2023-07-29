#include "../inc/Webserv.hpp"

Webserv* Webserv::_instance = 0;

Webserv* Webserv::getInstance()
{
	if (!_instance)
		_instance = new Webserv();
	return _instance;
}


void Webserv::config(std::string pathToFile)
{
	_config = Config::readConfig(pathToFile);
}

int	 Webserv::setup()
{

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
	if (_instance)
		delete _instance;
}
Webserv::Webserv(const Webserv& src) { (void)src; }
Webserv& Webserv::operator=(Webserv const& src) { (void)src; return *this; }