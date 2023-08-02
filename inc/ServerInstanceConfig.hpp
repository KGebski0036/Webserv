/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstanceConfig.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:49:32 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 17:25:38 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>
#include <map>
#define MAX_CLIENTS 10

struct ServerInstanceConfig
{
	ServerInstanceConfig()	//! TO BE DELETED
	{
		port = 80;
		serverName = "default";
		listenAddress = "0.0.0.0";
		rootDirectory = "/";
		indexFile = "index.html";
		allowedMethods.push_back("GET");
		allowedMethods.push_back("POST");
		allowedMethods.push_back("DELETE");

		autoindex = false;
		clientBodyBufferSize = 1000000000;
		errorPages[404] = "www/default_error_pages/404.html";
	}

	struct LocationConfig {
		
		~LocationConfig()
		{
			if (nestedLocation)
				delete nestedLocation;
		}

		std::string path;
		std::vector<std::string> allowedMethods;
		std::string root;
		std::string cgi_pass;
		std::string index;
		size_t clientBodyBufferSize;
		struct LocationConfig* nestedLocation;
	};

	int port;
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
