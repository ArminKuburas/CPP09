/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 11:25:02 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/12 01:28:03 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

std::string vector_to_string(std::vector<int> vec)
{
	std::string return_string = std::to_string(vec[0]);
	for (long unsigned int i = 1; i < vec.size(); i++)
	{
		return_string = return_string + " ";
		return_string = return_string + std::to_string(vec[i]);
	}
	return (return_string);
}

std::string deque_to_string(std::deque<int> deq)
{
	std::string return_string = std::to_string(deq[0]);
	for (long unsigned int i = 1; i < deq.size(); i++)
	{
		return_string = return_string + " ";
		return_string = return_string + std::to_string(deq[i]);
	}
	return (return_string);
}

MergeInsert::MergeInsert()
{
}

MergeInsert::~MergeInsert()
{
}

MergeInsert::MergeInsert(const MergeInsert &copy)
{
	*this = copy;
}

MergeInsert &MergeInsert::operator=(const MergeInsert &copy)
{
	if (this != &copy)
	{
		_vector = copy._vector;
		_deque = copy._deque;
	}
	return (*this);
}

std::vector<int> MergeInsert::VectorAlgorithm(std::string original_string)
{
	if (_vector.size() > 0)
		_vector.clear();
	std::string temp_string;
	int temp_int;
	for (long unsigned int i = 0; i <= original_string.length(); i++)
	{
		if (original_string[i] == ' ' || i == original_string.length())
		{
			temp_int = std::stoi(temp_string);
			_vector.push_back(temp_int);
			temp_string.clear();
		}
		else
			temp_string += original_string[i];
	}
	VectorRecursive(1);
	return (_vector);
}

void MergeInsert::VectorRecursive(int pair_size)
{
	int	pair_amount = _vector.size() / pair_size;
	if (pair_amount < 2)
		return;
	bool is_odd = pair_amount % 2 == 1;

	vec_iter start = _vector.begin();
	vec_iter end = (FindNext(FindNext(_vector.begin(), pair_size * pair_amount), -(is_odd * pair_size)));
	
	VecSwapPair(start, end, pair_size);
	VectorRecursive(pair_size * 2);
	std::vector<vec_iter> pending_insertion_chain;
	std::vector<vec_iter> main_chain;

	main_chain.insert(main_chain.end(), FindNext(_vector.begin(), pair_size - 1));
	main_chain.insert(main_chain.end(), FindNext(_vector.begin(), pair_size * 2 - 1));
	VecChainingTime(main_chain, pending_insertion_chain, pair_size, pair_amount);
	for (size_t i = 0; i < pending_insertion_chain.size(); i++)
	{
		std::vector<vec_iter>::iterator current_pend = FindNext(pending_insertion_chain.begin(), i);
		std::vector<vec_iter>::iterator current_main = 
		FindNext(main_chain.begin(), main_chain.size() - pending_insertion_chain.size() + i);
		std::vector<vec_iter>::iterator where_to_insert = std::upper_bound(main_chain.begin(), current_main, *current_pend, _compare<vec_iter>);
		main_chain.insert(where_to_insert, *current_pend);
	}
	if (is_odd)
	{
		vec_iter odd_pair = FindNext(end, pair_size - 1);
		std::vector<vec_iter>::iterator odd_where_to_insert =
			std::upper_bound(main_chain.begin(), main_chain.end(), odd_pair, _compare<vec_iter>);
		main_chain.insert(odd_where_to_insert, odd_pair);
	}

	std::vector<int> temp_vector;
	temp_vector.reserve(_vector.size());
	for (std::vector<vec_iter>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
	{
		for (int i = 0; i < pair_size; i++)
		{
			vec_iter pair_start = *it;
			std::advance(pair_start, -pair_size + i + 1);
			temp_vector.insert(temp_vector.end(), *pair_start);
		}
	}
	/* Replace the original values*/
	vec_iter main_vec_it = _vector.begin();
	vec_iter temp_it = temp_vector.begin();
	while (temp_it != temp_vector.end())
	{
		*main_vec_it = *temp_it;
		main_vec_it++;
		temp_it++;
	}
}

void MergeInsert::VecChainingTime(std::vector<vec_iter> & main_chain, std::vector<vec_iter> & pending_insertion_chain, int pair_size, int pair_amount)
{
	for (int i = 4; i <= pair_amount; i += 2)
	{
		pending_insertion_chain.insert(pending_insertion_chain.end(), FindNext(this->_vector.begin(), pair_size * (i - 1) - 1));
		main_chain.insert(main_chain.end(), FindNext(_vector.begin(), pair_size * i - 1));
	}
	int jacobsthal_prev = JacobsthalNumber(0);
	int inserted_amount = 0;
	for (int n = 1;; n++)
	{
		int jacobsthal_current = JacobsthalNumber(n);
		int jacobsthal_diff = jacobsthal_current - jacobsthal_prev;
		int offset = 0;
		if (jacobsthal_diff > static_cast<int>(pending_insertion_chain.size()))
			break;
		int number_of_insertions = jacobsthal_diff;
		std::vector<vec_iter>::iterator it_pend = FindNext(pending_insertion_chain.begin(), jacobsthal_diff - 1);
		std::vector<vec_iter>::iterator it_main = FindNext(main_chain.begin(), jacobsthal_current + inserted_amount);
		while (number_of_insertions > 0)
		{
			std::vector<vec_iter>::iterator where_to_insert = std::upper_bound(main_chain.begin(), it_main, *it_pend, _compare<vec_iter>);
			std::vector<vec_iter>::iterator inserted = main_chain.insert(where_to_insert, *it_pend);
			number_of_insertions--;
			it_pend = pending_insertion_chain.erase(it_pend);
			std::advance(it_pend, -1);
			offset += (inserted - main_chain.begin()) == jacobsthal_current + inserted_amount;
			it_main = FindNext(main_chain.begin(), jacobsthal_current + inserted_amount - offset);
		}
		inserted_amount += jacobsthal_diff;
		jacobsthal_prev = jacobsthal_current;
	}
}

void MergeInsert::VecSwapPair(vec_iter start, vec_iter end, int pair_size)
{
	int jump_forward = pair_size * 2;
	for (vec_iter it = start; it != end; std::advance(it, jump_forward))
	{
		vec_iter this_pair = FindNext(it, pair_size - 1);
		vec_iter that_pair = FindNext(it, pair_size * 2 - 1);
		if (*this_pair > *that_pair)
		{
			vec_iter swap_start = FindNext(this_pair, -pair_size + 1);
			vec_iter swap_end = FindNext(swap_start, pair_size);
			while (swap_start != swap_end)
			{
				std::iter_swap(swap_start, FindNext(swap_start, pair_size));
				swap_start++;
			}
		}
	}
}

std::deque<int> MergeInsert::DequeAlgorithm(std::string original_string)
{
	if (this->_deque.size() > 0)
		this->_deque.clear();
	std::string temp_string;
	int temp_int;
	for (long unsigned int i = 0; i <= original_string.length(); i++)
	{
		if (original_string[i] == ' ' || i == original_string.length())
		{
			temp_int = std::stoi(temp_string);
			_deque.push_back(temp_int);
			temp_string.clear();
		}
		else
			temp_string += original_string[i];
	}
	DequeRecursive(1);
	return (_deque);
}

void MergeInsert::DequeRecursive(int pair_size)
{
	int	pair_amount = _deque.size() / pair_size;
	if (pair_amount < 2)
		return;
	bool is_odd = pair_amount % 2 == 1;

	deq_iter start = _deque.begin();
	deq_iter end = (FindNext(FindNext(_deque.begin(), pair_size * pair_amount), -(is_odd * pair_size)));
	
	DeqSwapPair(start, end, pair_size);
	DequeRecursive(pair_size * 2);
	std::deque<deq_iter> pending_insertion_chain;
	std::deque<deq_iter> main_chain;

	main_chain.insert(main_chain.end(), FindNext(_deque.begin(), pair_size - 1));
	main_chain.insert(main_chain.end(), FindNext(_deque.begin(), pair_size * 2 - 1));
	DeqChainingTime(main_chain, pending_insertion_chain, pair_size, pair_amount);
	for (size_t i = 0; i < pending_insertion_chain.size(); i++)
	{
		std::deque<deq_iter>::iterator current_pend = FindNext(pending_insertion_chain.begin(), i);
		std::deque<deq_iter>::iterator current_main = 
		FindNext(main_chain.begin(), main_chain.size() - pending_insertion_chain.size() + i);
		std::deque<deq_iter>::iterator where_to_insert = std::upper_bound(main_chain.begin(), current_main, *current_pend, _compare<deq_iter>);
		main_chain.insert(where_to_insert, *current_pend);
	}
	if (is_odd)
	{
		deq_iter odd_pair = FindNext(end, pair_size - 1);
		std::deque<deq_iter>::iterator odd_where_to_insert =
			std::upper_bound(main_chain.begin(), main_chain.end(), odd_pair, _compare<deq_iter>);
		main_chain.insert(odd_where_to_insert, odd_pair);
	}

	std::deque<int> temp_deque;
	for (std::deque<deq_iter>::iterator it = main_chain.begin(); it != main_chain.end(); it++)
	{
		for (int i = 0; i < pair_size; i++)
		{
			deq_iter pair_start = *it;
			std::advance(pair_start, -pair_size + i + 1);
			temp_deque.insert(temp_deque.end(), *pair_start);
		}
	}
	/* Replace the original values*/
	deq_iter main_deq_it = _deque.begin();
	deq_iter temp_it = temp_deque.begin();
	while (temp_it != temp_deque.end())
	{
		*main_deq_it = *temp_it;
		main_deq_it++;
		temp_it++;
	}
}

void MergeInsert::DeqSwapPair(deq_iter start, deq_iter end, int pair_size)
{
	int jump_forward = pair_size * 2;
	for (deq_iter it = start; it != end; std::advance(it, jump_forward))
	{
		deq_iter this_pair = FindNext(it, pair_size - 1);
		deq_iter that_pair = FindNext(it, pair_size * 2 - 1);
		if (*this_pair > *that_pair)
		{
			deq_iter swap_start = FindNext(this_pair, -pair_size + 1);
			deq_iter swap_end = FindNext(swap_start, pair_size);
			while (swap_start != swap_end)
			{
				std::iter_swap(swap_start, FindNext(swap_start, pair_size));
				swap_start++;
			}
		}
	}
}

void MergeInsert::DeqChainingTime(std::deque<deq_iter> & main_chain, std::deque<deq_iter> & pending_insertion_chain, int pair_size, int pair_amount)
{
	for (int i = 4; i <= pair_amount; i += 2)
	{
		pending_insertion_chain.insert(pending_insertion_chain.end(), FindNext(this->_deque.begin(), pair_size * (i - 1) - 1));
		main_chain.insert(main_chain.end(), FindNext(_deque.begin(), pair_size * i - 1));
	}
	int jacobsthal_prev = JacobsthalNumber(0);
	int inserted_amount = 0;
	for (int n = 1;; n++)
	{
		int jacobsthal_current = JacobsthalNumber(n);
		int jacobsthal_diff = jacobsthal_current - jacobsthal_prev;
		int offset = 0;
		if (jacobsthal_diff > static_cast<int>(pending_insertion_chain.size()))
			break;
		int number_of_insertions = jacobsthal_diff;
		std::deque<deq_iter>::iterator it_pend = FindNext(pending_insertion_chain.begin(), jacobsthal_diff - 1);
		std::deque<deq_iter>::iterator it_main = FindNext(main_chain.begin(), jacobsthal_current + inserted_amount);
		while (number_of_insertions > 0)
		{
			std::deque<deq_iter>::iterator where_to_insert = std::upper_bound(main_chain.begin(), it_main, *it_pend, _compare<deq_iter>);
			std::deque<deq_iter>::iterator inserted = main_chain.insert(where_to_insert, *it_pend);
			number_of_insertions--;
			it_pend = pending_insertion_chain.erase(it_pend);
			std::advance(it_pend, -1);
			offset += (inserted - main_chain.begin()) == jacobsthal_current + inserted_amount;
			it_main = FindNext(main_chain.begin(), jacobsthal_current + inserted_amount - offset);
		}
		inserted_amount += jacobsthal_diff;
		jacobsthal_prev = jacobsthal_current;
	}
}

/**
 * Please look at wikipedia for a reference of Jacobsthal numbers.
 * The formula is typically as follows:
 * round((pow(2, n) - pow(-1, n)) / 3)
 * So why do we do + 2? Because if you take a look at the our book source.
 * It starts its sequence at the second 1 instead of at 0.
 * So it goes 1, 3, 5, 11, ...
 * Fun...
 * So why do we even need this stinky binky number?
 * It tells us the order in which we will binary insert the pending numbers into the main chain.
 */
int MergeInsert::JacobsthalNumber(int n)
{
	int jacobsthal_number = round((pow(2, n + 2) - pow(-1, n + 2)) / 3);
	return (jacobsthal_number);
}