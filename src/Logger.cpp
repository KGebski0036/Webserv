/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:53:29 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 19:09:38 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Logger.hpp"

void Logger::print(LogLevel level, std::string str, bool error) {
	if (level <= _level) {
		time_t rawtime;
		struct tm* tm;
		char buf[32];

		time(&rawtime);
		tm = localtime (&rawtime);
		int ret = strftime(buf, 32, "%T", tm);
		buf[ret] = '\0';

		printToFile(str, error, buf);
		printIO(BLUE, str, error, buf);
	}
}

void Logger::print(LogLevel level,std::string color, std::string str, bool error) {
	if (level <= _level) {
		time_t rawtime;
		struct tm* tm;
		char buf[32];

		time(&rawtime);
		tm = localtime (&rawtime);
		int ret = strftime(buf, 32, "%T", tm);
		buf[ret] = '\0';
		printToFile(str, error, buf);
		printIO(color, str, error, buf);
	}
}

void Logger::printToFile(std::string str, bool error, char* time)
{
	if (error)
		_logFile << "[" << time << "] " << "[ERROR] " << str << E << std::endl;
	else
		_logFile << "[" << time << "] " << str << E << std::endl;
}

void Logger::printIO(std::string color, std::string str, bool error, char* time)
{
	if (error)
		std::cerr << G << "[" << time << "] " << C_ERROR << BOLD << str << E;
	else
		std::cout << G << "[" << time << "] " << color << str << E;
}

Logger::Logger(LogLevel level) : _level(level) {
	_logFile.open("webserv.log", std::ios::out | std::ios::trunc);
	if (!_logFile.is_open()) {
		std::cerr << "Error opening log file" << E;
	}
}

Logger::~Logger() {
	if (_logFile.is_open())
		_logFile.close();
}

Logger::Logger() : _level(NONE) {}
Logger::Logger(const Logger& src) : _level(NONE) { (void)src;}
Logger& Logger::operator=(Logger const& src) { (void)src; return *this; }
