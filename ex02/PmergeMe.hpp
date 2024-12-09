/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 22:09:29 by akuburas          #+#    #+#             */
/*   Updated: 2024/12/09 12:52:52 by akuburas         ###   ########.fr       */
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

		VectorAlgorithm(std::string original_string);
		DequeAlgorithm(std::string original_string);	
	private:
		vector<int> _original_vector;
		deque<int> _original_deque;
		vector<int> _sorted_vector;
		deque<int> _sorted_deque;
}