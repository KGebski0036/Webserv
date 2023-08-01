/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstance.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 17:33:29 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 16:11:30 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ServerInstance.hpp"


// void ServerInstance::config()
// {
// 	_config = Config::readConfig(pathToFile);
// 	for (size_t i = 0; i < _config->getServersConfigs().size(); i++)
// 		std::cout << SYS_MSG << "Server config[" << i + 1 << "]" << E << _config->getServersConfigs()[i] << E;
// }

int	 ServerInstance::setup()
{
	
	try
	{
		_socketFd = createSocket();
		std::cout << "socket fd" << _socketFd << E;
	} catch (const MyException &e) { std::cerr << e.what();}
	return 0;
}
		
void ServerInstance::run()
{
	std::vector<struct pollfd> clientFds(MAX_CLIENTS + 1);
	clientFds[0].fd = _socketFd;
	clientFds[0].events = POLLIN; // Monitor for incoming connections
	int numSockets = 1;

	if (listen(_socketFd, SOMAXCONN) == -1)
		throw MyException("Listen on the socket failed", __func__, __FILE__, __LINE__);

	while(42) {
		int ready = poll(&clientFds[0], numSockets, -1);

		if (ready == -1)
			throw MyException("Error while polling for events", __func__, __FILE__, __LINE__);

		if (clientFds[0].revents & POLLIN) {
			struct sockaddr_in clientAddr;
			socklen_t clientAddrLen = sizeof(clientAddr);
			int clientSockfd = accept(_socketFd, (struct sockaddr*)&clientAddr, &clientAddrLen);
			if (clientSockfd == -1) {
				perror("accept");
			} else {
				// Add client socket to pollfd array
				if (numSockets == MAX_CLIENTS + 1) {
					std::cerr << "Maximum number of clients reached. Rejecting new connection." << std::endl;
					close(clientSockfd);
				} else {
					clientFds[numSockets].fd = clientSockfd;
					clientFds[numSockets].events = POLLIN; // Monitor for incoming data
					++numSockets;
				}
			}
		}

		for (int i = 1; i < numSockets; ++i) {
			if (clientFds[i].revents & POLLIN) {
				// handleClientData(clientFds[i].fd);
				char buffer[8000];
				int r = read(clientFds[i].fd, buffer, sizeof(buffer));
				buffer[r] = '\0';
					
				std::string response = getResponse(buffer);
				sendHttpResponse(clientFds[i].fd, response);
				// std::cout << SYS_MSG << "Connection from client " << E;
			}
		}
	}

}

void ServerInstance::sendHttpResponse(int clientSockfd, const std::string& response) {
    std::string httpResponse = "HTTP/1.1 " + ErrorPages::getHttpStatusMessage(_response_code)  + "\r\n";
    httpResponse += "Content-Length: " + std::to_string(response.length()) + "\r\n";
    httpResponse += "Content-Type: text/html\r\n";
    httpResponse += "\r\n"; // Empty line separates headers from the response body
    httpResponse += response;

    // Send the response to the client
    if (send(clientSockfd, httpResponse.c_str(), httpResponse.length(), 0) == -1) {
        perror("send");
    }
}

std::string ServerInstance::getResponse(std::string buffer)
{
	std::stringstream ss;
	ss << buffer;
	
	std::string protocolType;
	std::string requestedFile;

	ss >> protocolType;
	ss >> requestedFile;
	
	std::cout << SYS_MSG << MAGENTA << "Server: " << BLUE << _instanceConfig.listenAddress << ":" << _instanceConfig.port << E;
	std::cout << MAGENTA << "Method: " << GREEN << protocolType << " " << DARKBLUE << requestedFile << E << '\n';

	std::string tmp;
	std::ifstream file;
	
	if (requestedFile == "/")
	{
		file.open((_instanceConfig.rootDirectory + "/" + _instanceConfig.indexFile).c_str());
		std::cout << GREEN << "We return the " << _instanceConfig.rootDirectory + "/" + _instanceConfig.indexFile << " file" << E;
	}
	else
	{
		file.open((_instanceConfig.rootDirectory + requestedFile).c_str());
		std::cout << GREEN << "We return the " << _instanceConfig.rootDirectory + requestedFile << " file" << E;
	}
	if (file.is_open())
	{
		getline(file, tmp, '\0');
		file.close();
		_response_code = 200;
	}
	else
	{
		_response_code = 404;
		file.open(_instanceConfig.rootDirectory + "/default_error_pages/404.html");
		if (file.is_open())
		{
			getline(file, tmp, '\0');
			file.close();
		}
		else
			tmp = ErrorPages::generateErrorPage(_response_code);
	}
	return tmp;
}

void ServerInstance::clean()
{

}

int ServerInstance::createSocket() {
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd == -1)
		throw MyException("Socket creation failed", __func__, __FILE__, __LINE__);


	struct sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(_instanceConfig.listenAddress.c_str());
	serverAddr.sin_port = htons(_instanceConfig.port);

	if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
		throw MyException("Binding the socket failed", __func__, __FILE__, __LINE__);

	return sockfd;
}

int const & ServerInstance::getResponseCode() const { return _response_code; }

ServerInstance::ServerInstance(const ServerInstanceConfig& instanceConfig) : _instanceConfig(instanceConfig) {
	try {
		setup();
		run();
	} catch (const MyException &e) { std::cerr << e.what();}
}

ServerInstance::~ServerInstance() {}

ServerInstance::ServerInstance(const ServerInstance& src)  : _instanceConfig(src._instanceConfig) { (void)src; }
ServerInstance& ServerInstance::operator=(ServerInstance const& src) { (void)src; return *this; }
