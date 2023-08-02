/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MIMEtypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:56:02 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/02 10:40:42 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MIMEtypes.hpp"

const std::map<std::string, std::string> MIMEtypes::_MIMEtypes = MIMEtypes::createMIMEtypes();

std::map<std::string, std::string> MIMEtypes::createMIMEtypes()
{
    std::map<std::string, std::string> mimeTypes;
    mimeTypes["html"] = "text/html";
    mimeTypes["css"] = "text/css";
    mimeTypes["js"] = "application/javascript";
    mimeTypes["png"] = "image/png";
    mimeTypes["jpg"] = "image/jpeg";
    mimeTypes["jpeg"] = "image/jpeg";
    mimeTypes["gif"] = "image/gif";
    mimeTypes["ico"] = "image/x-icon";
    return mimeTypes;
}

std::string MIMEtypes::getMIMEtype(const std::string &filePath)
{
    size_t dotPos = filePath.find_last_of(".");
    if (dotPos == std::string::npos)
        return "text/html";

    std::string fileExt = filePath.substr(dotPos + 1);
    std::map<std::string, std::string>::const_iterator it = _MIMEtypes.find(fileExt);
    if (it != _MIMEtypes.end())
        return it->second;
    return "text/html";
}
