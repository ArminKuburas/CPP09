/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:47 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/01 09:52:59 by akuburas         ###   ########.fr       */
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
	std::getline(file, line);
	if (line != "date,exchange_rate")
		throw std::runtime_error("Error: Invalid database format");
	while (std::getline(file, line))
	{
		BitcoinExchange::checkLine(line);
		std::string date = line.substr(0, 10);
		double price = std::stod(line.substr(11));
		_database[date] = price;
	}
}

void BitcoinExchange::checkLine(const std::string &line) const
{
	size_t date_size = 10;
	bool dot_switch = false;
	
	for (size_t i = 0; i < line.size(); i++)
	{
		if (i == date_size)
		{
			if (line[i] != ',')
				throw std::runtime_error("Error: Invalid database format");
			continue;
		}
		if (i == 4 || i == 7)
		{
			if (line[i] != '-')
				throw std::runtime_error("Error: Invalid database format");
			continue;
		}
		if (i < date_size && (line[i] < '0' || line[i] > '9'))
			throw std::runtime_error("Error: Invalid database format");
		if (i > date_size && (line[i] < '0' || line[i] > '9') && line[i] != '.') 
			throw std::runtime_error("Error: Invalid database format");
		if (line[i] == '.') 
		{
			if (dot_switch)
				throw std::runtime_error("Error: Invalid database format");
			dot_switch = true;
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
	std::tm tm = {};
	std::istringstream ss(date);
	ss >> std::get_time(&tm, "%Y-%m-%d");
	if (ss.fail())
		return (false);
	tm.tm_isdst = -1;
	std::time_t t = std::mktime(&tm);
	if (t == -1)
		return (false);
	std::tm *normalized = std::localtime(&t);
	bool result = normalized->tm_year + 1900 == tm.tm_year &&
		normalized->tm_mon + 1 == tm.tm_mon + 1 &&
		normalized->tm_mday == tm.tm_mday;
	return (!result);
}

bool BitcoinExchange::isValueValid(const std::string &price) const
{
	if (price.empty())
		return (false);
	bool dot_switch = false;
	for (size_t i = 0; i < price.size(); i++)
	{
		if (i == 0 && price[i] == '-')
			continue;
		if (price[i] == '.')
		{
			if (dot_switch)
				return (false);
			dot_switch = true;
			continue;
		}
		if (price[i] < '0' || price[i] > '9')
			return (false);
	}
	return (true);
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	if (inputFile.empty())
		throw std::runtime_error("Error: Could not open file");
	std::ifstream file(inputFile);
	if (!file.is_open())
		throw std::runtime_error("Error: Could not open file");
	std::string line;
	std::getline(file, line);
	if (line != "date | value")
		throw std::runtime_error("Error: Invalid input format");
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
			std::cerr << "Error: bad date input => " << date << std::endl;
			continue;
		}
		if (!isValueValid(valueStr))
		{
			std::cerr << "Error: bad value input => " << valueStr << std::endl;
			continue;
		}
		double value = std::stod(valueStr);
		if (value < 0)
		{
			std::cerr << "Error: not a positive number" << std::endl;
			continue;
		}
		if (value > std::numeric_limits<int>::max())
		{
			std::cerr << "Error: too large a number" << std::endl;
			continue;
		}
		double closestPrice = findClosestPrice(date);
		double result = value * closestPrice;
		std::cout << std::setprecision(8) << date << " => " << value << " = " << result << std::endl;
	}
}