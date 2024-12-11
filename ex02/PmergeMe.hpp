/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/11 19:01:46 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <cmath>

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
		std::deque<int> _original_deque;
		std::deque<int> _sorted_deque;
		std::vector<int>::iterator VecFindNextIterator(std::vector<int>::iterator it, int steps);
		void VectorRecursive(int pair_size);
		void VecSwapPair(std::vector<int>::iterator start, vector<int>::iterator end, int pair_size);
		void VecChainingTime(std::vector<std::vector<int>::iterator> & main_chain, std::vector<std::vector<int>::iterator> & pending_insertion_chain, int pair_size, int pair_amount);
		int JacobsthalNumber(int n);
};