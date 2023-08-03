/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:33:04 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 18:34:37 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Request.hpp"

Request::Request() {}
Request::~Request() {}
Request::Request(const Request& src) { (void)src; }
Request& Request::operator=(Request const& src) { (void)src; return *this; }
