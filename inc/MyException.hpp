/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MyException.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 08:45:36 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/09 19:47:20 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Colors.hpp"

class MyException {
  public :
	MyException();
	MyException(const std::string& arg, const char* func, const char* file, int line);
	MyException(MyException const &);
	~MyException();
	MyException& operator=(MyException const &);
	const char* what() const throw();
  private :
	std::string msg;
};
