#include "../inc/Webserv.hpp"

void* Webserv::serverThreadFunction(void* arg) {
	ServerInstance* serverInstance = static_cast<ServerInstance*>(arg);
	try {
	    serverInstance->run();
	} catch (const MyException &e) { std::cerr << e.what();}
    return NULL;
}

void Webserv::config(std::string pathToFile)
{
	_config = Config::readConfig(pathToFile);

	for (size_t i = 0; i < _config->getServersConfigs().size(); i++)
	{
		ServerInstance* server = new ServerInstance(_config->getServersConfigs()[i]);

		pthread_t* thread = new pthread_t;
		_serverThreads.push_back(thread);

		int result = pthread_create(_serverThreads[i], NULL, &serverThreadFunction, server);

	    if (result != 0) {
			delete server;
			continue;
		}

		_servers.push_back(server);
	}
	for (size_t i = 0; i < _serverThreads.size(); ++i) {
		pthread_join(*(_serverThreads[i]), NULL);
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
