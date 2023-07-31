/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstanceConfig.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:49:32 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 19:33:16 by cjackows         ###   ########.fr       */
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
		std::string path;                         // URL path for the location
		std::vector<std::string> allowedMethods;  // Allowed HTTP methods for this location
		std::string root;                         // Root directory for serving files in this location
		std::string index;                        // Default index file for this location
	};

	int port;                                     	// Port number to listen on (e.g., 8000)
	std::string serverName;                       // Server name
	std::string listenAddress;                    // Address to listen on (e.g., "0.0.0.0")
	std::string rootDirectory;                    // Root directory for serving files for the server
	std::string indexFile;                        // Default index file for the server
	std::vector<std::string> allowedMethods;      // Allowed HTTP methods for the server
	std::vector<LocationConfig> locations;        // Vector to store location-specific configurations

	bool autoindex;
	size_t	clientBodyBufferSize;
	std::map<int, std::string> errorPages;
};
