/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/11 20:50:35 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>

using vec_iter = std::vector<int>::iterator;

class MergeInsert
{
	public:
		MergeInsert();
		~MergeInsert();
		MergeInsert(const MergeInsert &copy);
		MergeInsert &operator=(const MergeInsert &copy);

		void VectorAlgorithm(std::string original_string);
		void DequeAlgorithm(std::string original_string);	
	private:
		std::vector<int> _vector;
		std::deque<int> _deque;
		void VectorRecursive(int pair_size);
		void VecSwapPair(vec_iter start, vec_iter end, int pair_size);
		void VecChainingTime(std::vector<vec_iter> & main_chain, std::vector<vec_iter> & pending_insertion_chain, int pair_size, int pair_amount);
		int JacobsthalNumber(int n);
};

template <typename T> bool _compare(T a, T b)
{
	return (*a < *b);
}

template <typename T> T FindNext(T it, int amount_of_jumps)
{
	std::advance(it, amount_of_jumps);
	return (it);
}