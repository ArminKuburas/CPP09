/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:25:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/11 12:28:08 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

MergeInsert::MergeInsert()
{
	std::cout << "MergeInsert constructor called" << std::endl;
}

MergeInsert::~MergeInsert()
{
	std::cout << "MergeInsert destructor called" << std::endl;
}

MergeInsert::MergeInsert(const MergeInsert &copy)
{
	std::cout << "MergeInsert copy constructor called" << std::endl;
	*this = copy;
}

MergeInsert &MergeInsert::operator=(const MergeInsert &copy)
{
	std::cout << "MergeInsert assignation operator called" << std::endl;
	if (this != &copy)
	{
		_original_vector = copy._original_vector;
		_original_deque = copy._original_deque;
		_sorted_vector = copy._sorted_vector;
		_sorted_deque = copy._sorted_deque;
	}
	return (*this);
}

void MergeInsert::VectorAlgorithm(std::string original_string)
{
	if (this->_original_vector.size() > 0)
		this->_original_vector.clear();
	std::cout << "VectorAlgorithm called" << std::endl;
	std::string temp_string;
	int temp_int;
	for (long unsigned int i = 0; i < original_string.length(); i++)
	{
		if (original_string[i] == ' ')
		{
			temp_int = std::stoi(temp_string);
			_original_vector.push_back(temp_int);
			temp_string.clear();
		}
		else
			temp_string += original_string[i];
	}
	
}

void MergeInsert::DequeAlgorithm(std::string original_string)
{
	if (this->_original_deque.size() > 0)
		this->_original_deque.clear();
	std::cout << "DequeAlgorithm called" << std::endl;
	std::string temp_string;
	int temp_int;
	for (long unsigned int i = 0; i < original_string.length(); i++)
	{
		if (original_string[i] == ' ')
		{
			temp_int = std::stoi(temp_string);
			_original_deque.push_back(temp_int);
			temp_string.clear();
		}
		else
			temp_string += original_string[i];
	}
}	