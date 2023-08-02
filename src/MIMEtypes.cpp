/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MIMEtypes.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 09:56:02 by gskrasti          #+#    #+#             */
/*   Updated: 2023/08/02 11:54:34 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/MIMEtypes.hpp"

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

const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";

std::string base64_encode(const std::string &input) {
    std::string encoded;
    encoded.reserve((input.length() + 2) / 3 * 4);

    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    for (std::size_t index = 0; index < input.length(); ++index) {
        char_array_3[i++] = input[index];
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xFC) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xF0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0F) << 2) + ((char_array_3[2] & 0xC0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3F;

            for (i = 0; i < 4; i++)
                encoded += base64_chars[char_array_4[i]];

            i = 0;
        }
    }
    
    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xFC) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xF0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0F) << 2) + ((char_array_3[2] & 0xC0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3F;

        for (j = 0; j < i + 1; j++)
            encoded += base64_chars[char_array_4[j]];

        while (i++ < 3)
            encoded += '=';
    }

    return encoded;
}
