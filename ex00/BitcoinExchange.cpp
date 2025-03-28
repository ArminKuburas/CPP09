/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:47 by akuburas          #+#    #+#             */
/*   Updated: 2025/03/28 03:13:57 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	_monthLengths = { {1, 31}, {2, 28}, {3, 31}, {4, 30}, {5, 31}, {6, 30}, {7, 31}, {8, 31}, {9, 30}, {10, 31}, {11, 30}, {12, 31} };
	loadDatabase(databaseFile);
}

void BitcoinExchange::loadDatabase(const std::string &databaseFile)
{
	std::string fileExtension = ".csv";
	if (databaseFile.size() <= fileExtension.size() || databaseFile.substr(databaseFile.size() - fileExtension.size()) != fileExtension)
	{
    	throw std::runtime_error("Error: File is not a CSV");
	}
	
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
		if (!isDateValid(date))
			throw std::runtime_error("Error: Invalid database format");
		double price = std::stod(line.substr(11));
		if (price < 0)
		{
			throw std::runtime_error("Error: Invalid database format");
		}
		if (price > std::numeric_limits<int>::max())
		{
			throw std::runtime_error("Error: Invalid database format");
		}
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
			return (it->second);
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
	if (tm.tm_mon == 1 && tm.tm_mday == 29)
    {
		int year = tm.tm_year + 1900;
		if ((year % 4 != 0) || (year % 100 == 0 && year % 400 != 0))
			return false;
    }
	else if (tm.tm_mday > _monthLengths.at(tm.tm_mon + 1))
	{
		return (false);
	}
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

bool BitcoinExchange::isValueValid(const std::string &amount) const
{
	if (amount.empty())
		return (false);
	bool dot_switch = false;
	
	for (size_t i = 0; i < amount.size(); i++)
	{
		if (i == 0 && amount[i] == '-')
			continue;
		if (amount[i] == '.')
		{
			if (dot_switch)
				return (false);
			dot_switch = true;
			continue;
		}
		if (amount[i] < '0' || amount[i] > '9')
			return (false);
	}
	return (true);
}

void BitcoinExchange::processInput(const std::string &inputFile) const
{
	if (_database.empty())
		throw std::runtime_error("Error: Database is empty");
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
		if (!isDateValid(date) || isDateBefore(date))
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
		if (value < 0 || valueStr[0] == '-')
		{
			std::cerr << "Error: not a positive number." << std::endl;
			continue;
		}
		/*Bitcoin is divisble to 8 decimal places. Fun fact This smallest unit is referred to as a satoshi*/
		/*So thats 8 plus 4 since we can only go up to 1000 and plus 1 for the decimal point itself the .*/
		/*So the biggest string you can input affectively should be something like 1000.00000000*/
		/*Although I think floats can only go up to like 6-7 decimal points lol*/
		/*A doubles precision is pretty huge though. So somewhat hard to overflow with all these checks and balances*/
		if (value > 1000 || valueStr.size() > 13)
		{
			std::cerr << "Error: too large a number." << std::endl;
			continue;
		}
		double closestPrice = findClosestPrice(date);
		double result = value * closestPrice;
		std::cout << std::setprecision(8) << date << " => " << value << " = " << result << std::endl;
	}
}

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::~BitcoinExchange()
{
}

std::map<std::string, double> BitcoinExchange::getDatabase() const
{
	return (_database);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	this->_database = other.getDatabase();
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	this->_database = other.getDatabase();
	return (*this);
}

void BitcoinExchange::setDatabase(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

bool BitcoinExchange::isDateBefore(const std::string &date) const
{
	if (_database.empty())
		return (false);
	std::string earliestDate = _database.begin()->first;
	std::tm inputTm = {};
	std::tm earliestTm = {};
	std::istringstream inputSs(date);
	std::istringstream earliestSs(earliestDate);
	inputSs >> std::get_time(&inputTm, "%Y-%m-%d");
	earliestSs >> std::get_time(&earliestTm, "%Y-%m-%d");
	
	std::time_t inputTime = std::mktime(&inputTm);
	std::time_t earliestTime = std::mktime(&earliestTm);
	return (inputTime < earliestTime);
}