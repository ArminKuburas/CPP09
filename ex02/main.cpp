/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:36:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/10 14:07:32 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <climits>

bool validate_individual_argument(std::string input)
{
	if (input[0] == '-')
	{
		std::cerr << "Invalid Input: negative value provided" << std::endl;
		return (false);
	}
	long converted_number = strtol(input.c_str(), NULL, 10);
	if (converted_number == 0 && input != "0")
	{
		std::cerr << "Invalid Input: non/number argument was provided" << std::endl;
		return (false);
	}
	if (converted_number > INT_MAX || errno == ERANGE)
	{
		std::cerr << "Invalid Input: a number larger then int max was provided" << std::endl;
		return (false);
	}
	if (input != std::to_string(converted_number))
	{
		std::cerr << "Invalid Input: non-number elements found within input" << std::endl;
	}
	return (true);
}

bool validate_input(int argc, char **argv)
{
	std::vector<long> numbers;
	for (int i = 1; i < argc; i++)
	{
		std::string input = argv[i];
		if (validate_individual_argument(input) == false)
			return (false);
		numbers.push_back(strtol(input.c_str(), NULL, 10));
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (argc < 3)
	{
		std::cerr << "Usage: ./PmergeMe [unique_number] [unique_number] [unique_number]" << std::endl;
		return (1);
	}
	if (validate_input(argc, argv) == false)
		return (1);
	
	return (0);
}