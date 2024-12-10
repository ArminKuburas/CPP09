/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:36:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/10 10:52:50 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool validate_input(int argc, char **argv)
{
	bool space_collector = true;
	for (int i = 1; i <= argc; i++)
	{
		std::string input = argv[i];
		std::string::iterator it = input.begin();
		while (it != input.end())
		{
			if (std::isdigit(*it) == false && (*it != ' ' || (space_collector == true && *it == ' ')))
				return (false);
			else if ((space_collector = true && std::isdigit(*it) == true))
				space_collector = false;
			else if (*it == ' ')
				space_collector = true;
			it++;
		}
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./PmergeMe [string of unique numbers];\nUsage: ./PmergeMe [multiple] [strings] [of] [input];\n./PmergeMe [mixed inputs]" << std::endl;
		return (1);
	}
	if (validate_input(argc, argv) == false)
	{
		std::cerr << "Invalid input" << std::endl;
		return (1);
	}
	return (0);
}