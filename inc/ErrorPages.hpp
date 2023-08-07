/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kgebski <kgebski@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:16:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/07 19:02:39 by kgebski          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ServerInstanceConfig.hpp"
#include "Colors.hpp"

class ErrorPages
{
public:
    static std::string getHttpStatusMessage(int errorCode);
    static std::string generateErrorPage(int errorCode, ServerInstanceConfig serverConf);
private:
    std::map<int, std::string> _httpStatusMessages;

    ErrorPages();
    ErrorPages(const ErrorPages &);
    ErrorPages &operator=(const ErrorPages &);
    ~ErrorPages();
};
