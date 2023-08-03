/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:49:26 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/03 17:32:07 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

class Client {
  public:
	Client();
	Client(int);
	~Client();
	Client& operator=(Client const &);

  private:
	int _clientSocket;
	Client(const Client&);
};
