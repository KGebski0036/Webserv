/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstanceConfig.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:49:32 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 19:47:12 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <map>
#include <netinet/in.h>

struct LocationConfig {
	std::string path;
	std::vector<std::string> allowedMethods;
	std::string root;
	std::string cgi_pass;
	std::string index;
	size_t clientBodyBufferSize;
	struct LocationConfig* nestedLocation;
};

struct ServerInstanceConfig
{
	ServerInstanceConfig()
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
		clientBodyBufferSize = 100000;
		errorPages[404] = "default_error_pages/404.html";
	}

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
};
