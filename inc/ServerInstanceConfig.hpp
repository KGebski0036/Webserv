/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstanceConfig.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:49:32 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/07 05:33:35 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <map>
#include <netinet/in.h>

struct ServerInstanceConfig
{
	ServerInstanceConfig()	//! TO BE DELETED
	{
		port = 80;
		serverName = "default";
		listenAddress = "0.0.0.0";
		rootDirectory = "";
		indexFile = "index.html";
		allowedMethods.push_back("GET");
		allowedMethods.push_back("POST");
		allowedMethods.push_back("DELETE");

		autoindex = false;
		clientBodyBufferSize = 1000000000;
		errorPages[404] = "www/default_error_pages/404.html";
	}

	struct LocationConfig {
		std::string path; //? location path
		std::vector<std::string> allowedMethods;
		std::string root; //? CGI Folder? ~/cgi-bin
		std::string cgi_pass; //!
		std::string index;
		size_t clientBodyBufferSize;
		struct LocationConfig* nestedLocation;
	};

	int port;
	int listen_fd;
	struct sockaddr_in serverAddr;

	std::string serverName;
	std::string listenAddress;
	std::string rootDirectory;
	std::string indexFile;
	std::vector<std::string> allowedMethods;
	std::vector<LocationConfig> locations;

	bool autoindex;
	size_t	clientBodyBufferSize;
	std::map<int, std::string> errorPages;

	void displayLocationConfig(const LocationConfig& location) const {
		std::cout << "Path: " << location.path << std::endl;
		std::cout << "Allowed Methods: ";
		for (std::vector<std::string>::const_iterator it = location.allowedMethods.begin(); it != location.allowedMethods.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Root: " << location.root << std::endl;
		std::cout << "CGI Pass: " << location.cgi_pass << std::endl;
		std::cout << "Index: " << location.index << std::endl;
		std::cout << "Client Body Buffer Size: " << location.clientBodyBufferSize << std::endl;
		if (location.nestedLocation != nullptr) {
			std::cout << "Nested Location: " << std::endl;
			displayLocationConfig(*location.nestedLocation);
		}
	}

	void displayServerConfig() const {
		std::cout << "Port: " << port << std::endl;
		std::cout << "Listen FD: " << listen_fd << std::endl;
		std::cout << "Server Address: " << listenAddress << std::endl;
		std::cout << "Server Name: " << serverName << std::endl;
		std::cout << "Root Directory: " << rootDirectory << std::endl;
		std::cout << "Index File: " << indexFile << std::endl;
		std::cout << "Allowed Methods: ";
		for (std::vector<std::string>::const_iterator it = allowedMethods.begin(); it != allowedMethods.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Autoindex: " << (autoindex ? "true" : "false") << std::endl;
		std::cout << "Client Body Buffer Size: " << clientBodyBufferSize << std::endl;
		std::cout << "Error Pages: " << std::endl;
		for (std::map<int, std::string>::const_iterator it = errorPages.begin(); it != errorPages.end(); ++it) {
			std::cout << "  " << it->first << ": " << it->second << std::endl;
		}
		std::cout << "Locations: " << std::endl;
		for (std::vector<LocationConfig>::const_iterator it = locations.begin(); it != locations.end(); ++it) {
			displayLocationConfig(*it);
		}
	}
};
