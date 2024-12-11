/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/11 12:13:56 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once 

#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

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
		std::vector<int> _original_vector;
		std::deque<int> _original_deque;
		std::vector<int> _sorted_vector;
		std::deque<int> _sorted_deque;
};