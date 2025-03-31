/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 17:24:52 by akuburas          #+#    #+#             */
/*   Updated: 2025/03/31 13:03:45 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		if (argc > 2)
			std::cerr << "Error: Too many arguments" << std::endl;
		else
			std::cerr << "Error: could not open file." << std::endl;
		return (1);
	}
	try
	{
		BitcoinExchange exchange("data.csv");
		exchange.processInput(argv[1]);
	}
	catch (const std::exception &e)
	{
		if (std::string(e.what()) == "stoi")
			std::cerr << "Error: invalid input. Conversion of token into number failed." << std::endl;
		else
			std::cerr << "An error occured: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}