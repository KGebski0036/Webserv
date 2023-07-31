/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerInstanceConfig.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:49:32 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/31 14:00:20 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <vector>

struct ServerInstanceConfig
{
	struct LocationConfig {
		std::string path;                         // URL path for the location
		std::vector<std::string> allowedMethods;  // Allowed HTTP methods for this location
		std::string root;                         // Root directory for serving files in this location
		std::string index;                        // Default index file for this location
	};

	int port;                                     // Port number to listen on (e.g., 8000)
	std::string serverName;                       // Server name
	std::string listenAddress;                    // Address to listen on (e.g., "0.0.0.0")
	std::string rootDirectory;                    // Root directory for serving files for the server
	std::string indexFile;                        // Default index file for the server
	std::vector<std::string> allowedMethods;      // Allowed HTTP methods for the server
	std::vector<LocationConfig> locations;        // Vector to store location-specific configurations
};