/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:46:02 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 19:09:55 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "Colors.hpp"

enum LogLevel {
  NONE,
  INFO,
  DEBUG
};

class Logger {
  public:
	Logger(LogLevel level);
	~Logger();

	void print(LogLevel level, std::string str, bool error);
	void print(LogLevel level, std::string color, std::string str, bool error);

  private:
	const LogLevel _level;
	std::ofstream _logFile;

	void printIO(std::string color, std::string str, bool error, char* time);
	void printToFile(std::string str, bool error, char* time);

	Logger();
	Logger(const Logger&);
	Logger& operator=(Logger const &);
};
