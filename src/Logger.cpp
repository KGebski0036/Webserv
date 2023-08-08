/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 14:53:29 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/08 13:13:55 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Logger.hpp"

void Logger::print(LogLevel level, std::string str, bool error) {
	print(level, BLUE, str, error);
}

void Logger::print(LogLevel level, std::string color, std::string str, bool error) {
	if (str == "")
		return;
	if (level <= _level) {
		time_t rawtime;
		struct tm* tm;
		char buf[32];

		time(&rawtime);
		tm = localtime (&rawtime);
		int ret = strftime(buf, 32, "%T", tm);
		buf[ret] = '\0';

		std::ostringstream oss;

		oss << G << "[" << buf << "] ";
		if (level == DEBUG)
			oss << ORANGE << "[DEBUGGING] ";

		if (error)
			oss << C_ERROR << BOLD << str << E;
		else
			oss << color << str << E;

		std::string tmp;
		tmp = oss.str();
		std::cout << tmp;
		_logFile << trimColors(tmp);
		_logFile.flush();
	}
}

Logger::Logger(LogLevel level) : _level(level) {
	_logFile.open("webserv.log", std::ios::out | std::ios::trunc);
	if (!_logFile.is_open()) {
		std::cerr << "Error opening log file" << E;
	}
}

std::string Logger::trimColors(const std::string& input) {
	std::string result;
	bool insideEscapeSequence = false;

	for (std::size_t i = 0; i < input.size(); ++i) {
		char c = input[i];
		if (c == '\033') {
			insideEscapeSequence = true;
		} else if (insideEscapeSequence && c == 'm') {
			insideEscapeSequence = false;
		} else if (!insideEscapeSequence) {
			result += c;
		}
	}

	return result;
}

Logger::~Logger() {
	if (_logFile.is_open())
		_logFile.close();
}

Logger::Logger() : _level(NONE) {}
Logger::Logger(const Logger& src) : _level(NONE) { (void)src;}
Logger& Logger::operator=(Logger const& src) { (void)src; return *this; }
