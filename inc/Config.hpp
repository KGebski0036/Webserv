/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 14:30:01 by cjackows          #+#    #+#             */
/*   Updated: 2023/07/29 15:45:13 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Colors.hpp"
#include "MyException.hpp"

class Config : public MyException {
  public:
	static Config* readConfig(std::string pathToFile);
	
	Config();
	~Config();
	Config(const Config&);
	Config&	operator=(Config const &);

  private:
	std::vector<std::string> _fileVector;
  
	void readFile(std::string pathToFile);
};
