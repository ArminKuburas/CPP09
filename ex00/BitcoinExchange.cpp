/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:47 by akuburas          #+#    #+#             */
/*   Updated: 2024/10/31 10:06:56 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

void BitcoinExchange::loadDatabase(const std::string &databaseFile)
{
	std:: ifstream file(databaseFile);
	if (!file.is_open())
		throw std::runtime_error("Error: Could not open file");
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		double price;
		if (ss >> date >> price)
		{
			_database[date] = price;
		}
		else
		{
			throw std::runtime_error("Error: Invalid database format");
		}
	}
}

double BitcoinExchange::findClosestPrice(const std::string &date) const
{
	std::map<std::string, double>::const_iterator it = _database.lower_bound(date);
	if (it == _database.end() || it->first != date)
	{
		if (it == _database.begin())
			return (0.0);
		--it;
	}
	return (it->second);
}

bool BitcoinExchange::isDateValid(const std::string &date) const
{
	if (date.size() != 10)
		return (false);
	if (date[4] != '-' || date[7] != '-')
		return (false);
	for (int i = 0; i < 10; i++)
	{
		if (i == 4 || i == 7)
			continue;
		if (date[i] < '0' || date[i] > '9')
			return (false);
	}
	return (true);
}

bool BitcoinExchange::isValueValid(const std::string &price) const
{
	if (price.empty())
		return (false);
	for (size_t i = 0; i < price.size(); i++)
	{
		if (i == 0 && price[i] == '-')
			continue;
		if (price[i] < '0' || price[i] > '9')
			return (false);
	}
	return (true);
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	if (inputFile.empty())
		throw std::runtime_error("Error: Invalid input file");
	std::ifstream file(inputFile);
	if (!file.is_open())
		throw std::runtime_error("Error: Could not open file");
	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string date;
		std::string pipe;
		std::string valueStr;
		if (!(ss >> date >> pipe >> valueStr) || pipe != "|" )
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (!isDateValid(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
			continue;
		}
		if (!isValueValid(valueStr))
		{
			std::cerr << "Error: bad input => " << valueStr << std::endl;
			continue;
		}
		double value = std::stod(valueStr);
		double closestPrice = findClosestPrice(date);
		double result = value * closestPrice;
		std::cout << date << " => " << value << " = " << result << std::endl;
	}
	
}