/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Colors.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjackows <cjackows@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 15:21:41 by cjackows          #+#    #+#             */
/*   Updated: 2023/08/01 15:08:33 by cjackows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#ifdef __linux__
    #define OS_LINUX
    #define PROGRESS_DONE_CHAR '#'
    #define PROGRESS_TODO_CHAR '-'
#else
    #define OS_MAC
    #define PROGRESS_DONE_CHAR "🟩"
    #define PROGRESS_TODO_CHAR "⬜️"
#endif

		//* Custom colors, isnert + "<color code>m"
#define BASE_T "\033[38;5;"
#define BASE_B "\033[48;5;"

		//* System colors
#define	SYS_MSG_DES " \033[38;5;242m❯ \033[3m\033[38;5;242m\033[38;5;124m"
#define	SYS_MSG_CON " \033[38;5;242m❯ \033[3m\033[38;5;242m\033[38;5;28m"
#define	SYS_MSG "\033[38;5;242m❯ \033[3m\033[38;5;242m"
#define	SYS_MSG_B "\033[48;5;242m❯ \033[3m\033[38;5;242m "
#define SYS "\033[38;5;242m\033[4m\033[38;5;33m"
#define G "\033[38;5;242m"

		//* Utils boxes
#define ERROR "\033[48;5;160m[ ERROR ]\033[0m \033[38;5;196m"
#define EX "\033[48;5;160m[ EXCEPTION ]\033[0m \033[38;5;196m"
#define INFO "\033[48;5;39m[INFORMATION]\033[0m \033[38;5;123m"
#define DEBUG "\033[48;5;202m              [ DEBUGGING ]            \033[0m"
#define DEBUG_T "\033[38;5;202m"

		//* Quick actions
#define R "\033[0m" 	// reset
#define E "\033[0m\n"	// reset + new line
#define I "\033[7m"		// inverse text and background
#define DIM "\033[2m"	// makes color less vibrant

		//* More colors
#define BLACK "\033[38;5;0m"
#define WHITE "\033[38;5;255m"
#define RED "\033[38;5;162m"
#define GREEN "\033[1;32m"
#define BLUE "\033[38;5;81m"
#define PINK "\033[38;5;213m"
#define PURPLE "\033[38;5;135m"
#define ORANGE "\033[38;5;202m"
#define YELLOW "\033[38;5;214m"
#define MAGENTA "\033[38;5;127m"

		//* Text font settings
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define STRIKETHROUGH "\033[9m"

		//* Cursor
#define F "\r\033[K"
#define A "\033[0A"
