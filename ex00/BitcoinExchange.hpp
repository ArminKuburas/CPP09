/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:49 by akuburas          #+#    #+#             */
/*   Updated: 2025/02/19 14:17:39 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iomanip>
#include <limits>
#include <ctime>

class BitcoinExchange
{
	public:
		BitcoinExchange(const std::string &databaseFile);
		void processInput(const std::string &inputFile) const;
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);
		std::map<std::string, double> getDatabase() const;
		void setDatabase(const std::string &databaseFile);
		
	private:
		std::map<std::string, double> _database;
	
		void checkLine(const std::string &line) const;
		void loadDatabase(const std::string &databaseFile);
		double findClosestPrice(const std::string &date) const;
		bool isDateValid(const std::string &date) const;
		bool isValueValid(const std::string &price) const;
};