/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:51:10 by akuburas          #+#    #+#             */
/*   Updated: 2025/03/28 03:13:01 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "Usage: ./RPN \"expression\" or ./RPN \"argument\" \"argument\" \"argument\" ..." << std::endl;
		return (1);
	}
	try
	{
		if (argc == 2)
			std::cout << RPNCalculator::calculate(argv[1]) << std::endl;
		else
		{
			std::string expression = argv[1];
			for (int i = 2; i < argc; i++)
			{
				std::string arg = argv[i];
				if (arg.empty())
					throw std::runtime_error("empty argument");
				else
					expression += " " + arg;
			}
			std::cout << RPNCalculator::calculate(expression) << std::endl;
		}
	}
	catch (std::exception &e)
	{
		if (e.what() == std::string("stoi"))
			std::cerr << "Invalid Input. Conversion of token into integer failed" << std::endl;
		
		else
			std::cerr << "an error occured: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}