/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:49 by akuburas          #+#    #+#             */
/*   Updated: 2024/10/31 10:43:05 by akuburas         ###   ########.fr       */
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

class BitcoinExchange
{
	public:
		BitcoinExchange(const std::string &databaseFile);
		void processInput(const std::string &inputFile) const;
	private:
	std::map<std::string, double> _database;
	
	void checkLine(const std::string &line) const;
	void loadDatabase(const std::string &databaseFile);
	double findClosestPrice(const std::string &date) const;
	bool isDateValid(const std::string &date) const;
	bool isValueValid(const std::string &price) const;
};