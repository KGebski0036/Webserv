/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPages.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 15:16:55 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/01 16:15:09 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <map>
#include <sstream>

class ErrorPages
{
public:
    static std::string getHttpStatusMessage(int errorCode);
    static std::string generateErrorPage(int errorCode);
private:
    std::map<int, std::string> _httpStatusMessages;

    ErrorPages();
    ErrorPages(const ErrorPages &);
    ErrorPages &operator=(const ErrorPages &);
    ~ErrorPages();
};
