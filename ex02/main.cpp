/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:36:31 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/09 12:51:25 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

bool validate_input(std::string input)
{
	std::string::iterator it = input.begin();
	while (it != input.end())
	{
		if (std::isdigit(*it) == false && *it != ' ')
			return (false);
		it++;
	}
	return (true);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Usage: ./PmergeMe [string of unique numbers]" << std::endl;
		return (1);
	}
	if (validate_input(argv[1]) == false)
	{
		std::cerr << "Invalid input" << std::endl;
		return (1);
	}
}