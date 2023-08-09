/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:46:02 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 19:47:47 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdarg>
#include <iostream>
#include <string>
#include <ctime>
#include <cstdarg>
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
	std::string trimColors(const std::string& input);

  private:
	const LogLevel _level;
	std::ofstream _logFile;

	Logger();
	Logger(const Logger&);
	Logger& operator=(Logger const &);
};
