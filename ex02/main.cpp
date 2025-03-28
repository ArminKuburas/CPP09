/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:36:31 by akuburas          #+#    #+#             */
/*   Updated: 2025/03/28 02:54:34 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <climits>
#include <set>
#include <iomanip>

/**
 * Validates a single input argument
 * @param input The input string to validate.
 * @return True if the input is a valid positive integer within the int range, false otherwise.
 */
bool validate_individual_argument(std::string input)
{
	if (input[0] == '-')
	{
		std::cerr << "Invalid Input: negative value provided" << std::endl;
		return (false);
	}
	for (long unsigned int i = 0; i < input.size(); i++)
	{
		if (input[i] < '0' || input[i] > '9')
		{
			std::cerr << "Invalid Input: non-numeric character found" << std::endl;
			return (false);
		}
	}
	long converted_number = strtol(input.c_str(), NULL, 10);
	if (converted_number == 0 && input != "0")
	{
		std::cerr << "Invalid Input: non-number argument was provided" << std::endl;
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

/**
 * Validates and processes input arguments into a vector.
 * 
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return True if all inputs are valid and unique, false otherwise.
 */
bool validate_input_vec(int argc, char **argv)
{
	std::vector<long> numbers;
	for (int i = 1; i < argc; i++)
	{
		std::string input = argv[i];
		if (validate_individual_argument(input) == false)
			return (false);
		numbers.push_back(strtol(input.c_str(), NULL, 10));
	}
	std::set<long> unique_numbers(numbers.begin(), numbers.end());
	if (unique_numbers.size() != numbers.size())
	{
		std::cerr << "Invalid Input: non-unique numbers found" << std::endl;
		return (false);
	}
	return (true);
}

/**
 * Validates and processes input arguments into a deque.
 * 
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return True if all inputs are valid and unique, false otherwise.
 */
bool validate_input_deq(int argc, char **argv)
{
	std::deque<long> numbers;
	for (int i = 1; i < argc; i++)
	{
		std::string input = argv[i];
		if (validate_individual_argument(input) == false)
			return (false);
		numbers.push_back(strtol(input.c_str(), NULL, 10));
	}
	std::set<long> unique_numbers(numbers.begin(), numbers.end());
	if (unique_numbers.size() != numbers.size())
	{
		std::cerr << "Invalid Input: non-unique numbers found" << std::endl;
		return (false);
	}
	return (true);
}

/**
 * Converts command-line arguments into a single space-separated string.
 * 
 * @param argc The argument count.
 * @param argv The argument vector.
 * @return A string containing all arguments concatenated with spaces.
 */
std::string argv_to_string(int argc, char **argv)
{
	std::string return_string = argv[1];
	for (int i = 2; i < argc; i++)
	{
		return_string = return_string + " ";
		return_string = return_string + argv[i];
	}
	return (return_string);
}

int main(int argc, char **argv)
{
	try
	{
		MergeInsert sorter;
		if (argc < 3)
		{
			std::cerr << "Usage: ./PmergeMe [unique_number] [unique_number] [unique_number] ..." << std::endl;
			return (1);
		}
		if (validate_input_vec(argc, argv) == false)
			return (1);
		std::cout << "Before: " << argv_to_string(argc, argv) << std::endl;
		clock_t vec_start = clock();
		if (validate_input_vec(argc, argv) == false)
			return (1);
		std::vector<int> sorted_vec = sorter.VectorAlgorithm(argv_to_string(argc, argv));
		std::cout << "Vector After: " << vector_to_string(sorted_vec) << std::endl;
		clock_t vec_end = clock();
		double elapsed_vec = static_cast<double>(vec_end - vec_start) / CLOCKS_PER_SEC;

		clock_t deq_start = clock();
		if (validate_input_deq(argc, argv) == false)
			return (1);
		//The algorithm is the same for both containers. The only difference is the container type.
		//Deques differ from vectors in the way they store data.
		//Vectors store data in a continuous block of memory, while deques store data in a series of blocks.
		//This means that deques are slower when accessing elements in the middle of the container,
		//but faster when adding or removing elements from the front or back of the container.
		//This does mean that with our style of this algorithm that vectors tend to be faster since once we have a vector container
		//we don't need to add or remove elements from the front or back of the container. Until we merge  two vectors/deques together at a later state.
		std::deque<int> sorted_deq = sorter.DequeAlgorithm(argv_to_string(argc, argv));
		std::cout << "Deque After: " << deque_to_string(sorted_deq) << std::endl;
		clock_t deq_end = clock();
		double elapsed_deq = static_cast<double>(deq_end - deq_start) / CLOCKS_PER_SEC;
		std::cout << "VectorAlgorithm (Which uses the std::vector container) took " << std::fixed << std::setprecision(6) << elapsed_vec << " seconds" << std::endl;
		std::cout << "DequeAlgorithm (Which uses the std::deque container) took " << std::fixed << std::setprecision(6) << elapsed_deq << " seconds" << std::endl;
	}
	catch (std::exception &e)
	{
		std::cerr << "An error occurred: " << e.what() << std::endl;
	}
	return (0);
}