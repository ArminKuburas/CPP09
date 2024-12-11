/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:25:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/11 19:00:57 by akuburas         ###   ########.fr       */
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
	if (this->_vector.size() > 0)
		this->_vector.clear();
	std::cout << "VectorAlgorithm called" << std::endl;
	std::string temp_string;
	int temp_int;
	for (long unsigned int i = 0; i < original_string.length(); i++)
	{
		if (original_string[i] == ' ')
		{
			temp_int = std::stoi(temp_string);
			_vector.push_back(temp_int);
			temp_string.clear();
		}
		else
			temp_string += original_string[i];
	}
	VectorRecursive(1);
	
}

void MergeInsert::VectorRecursive(int pair_size)
{
	int	pair_amount = _vector.size() / pair_size;
	if (pair_amount < 2)
		return;
	bool is_odd = pair_amount % 2 == 1;

	std::vector<int>::iterator start = _vector.begin();
	std::vector<int>::iterator end = (VecFindNextIterator(VecFindNextIterator(_vector.begin(), pair_size * pair_amount), -(is_odd * pair_size)));
	
	VecSwapPair(start, end, pair_size);
	VectorRecursive(pair_size * 2);
	std::vector<std::vector<int>::iterator> pending_insertion_chain;
	std::vector<std::vector<int>::iterator> main_chain;

	main_chain.insert(main_chain.end(), VecFindNextIterator(_vector.begin(), pair_size - 1));
	main_chain.insert(main_chain.end(), VecFindNextIterator(_vector.begin(), pair_size * 2 - 1));
	
	VecChainingTime(main_chain, pending_insertion_chain, pair_size, pair_amount);
}

void VecChainingTime(std::vector<std::vector<int>::iterator> & main_chain, std::vector<std::vector<int>::iterator> & pending_insertion_chain, int pair_size, int pair_amount)
{
	for (int i = 4; i <= pair_amount; i += 2)
	{
		pending_insertion_chain.insert(pending_insertion_chain.end(), VecFindNextIterator(_vector.begin(), pair_size * (i - 1) - 1));
		main_chain.insert(main_chain.end(), VecFindNextIterator(_vector.begin(), pair_size * i - 1));
	}
	int jacobsthal_prev = JacobsthalNumber(1);
}

void MergeInsert::VecSwapPair(std::vector<int>::iterator start, vector<int>::iterator end, int pair_size)
{
	int jump_forward = pair_size * 2;
	for (std::vector<int>::iterator it = start; it != end; std::advance(it, jump_forward))
	{
		std::vector<int>::iterator this_pair = VecFindNextIterator(it, pair_size - 1);
		std::vector<int>::iterator that_pair = VecFindNextIterator(it, pair_size * 2 - 1);
		if (*this_pair > *that_pair)
		{
			std::vector<int>::iterator swap_start = VecFindNextIterator(this_pair, -pair_size + 1);
			std::vector<int>::iterator swap_end = VecFindNextIterator(swap_start, pair_size);
			while (swap_start != swap_end)
			{
				std::iter_swap(swap_start, VecFindNextIterator(swap_start, pair_size));
				swap_start++;
			}
		}
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

std::vector<int>::iterator MergeInsert::VecFindNextIterator(std::vector<int>::iterator it, int steps)
{
	std::advance(it, steps);
	return it;
}

int MergeInsert::JacobsthalNumber(int n)
{
	return (())
}