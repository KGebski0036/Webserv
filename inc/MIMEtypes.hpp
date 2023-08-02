/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MIMEtypes.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:50:09 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/02 11:47:33 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>
#include <string>

class MIMEtypes
{
public:
    static std::string getMIMEtype(const std::string & filePath);
private:
    static const std::map<std::string, std::string> _MIMEtypes;
    static std::map<std::string, std::string> createMIMEtypes();

    MIMEtypes();
    MIMEtypes(const MIMEtypes &);
    MIMEtypes & operator=(const MIMEtypes &);
    ~MIMEtypes();
};

std::string base64_encode(const std::string &input);
