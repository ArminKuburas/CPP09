/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge-insert.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:20:11 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/14 11:52:08 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>

void	binaryInsert(std::vector<int>& chain, int value)
{
	std::vector<int>::iterator it = std::lower_bound(chain.begin(), chain.end(), value);
	if (it == chain.end())
		chain.push_back(value);
	else
		chain.insert(it, value);
}

void mergeInsertSort(std::vector<int>& arr)
{
	if (arr.size() < 2)
		return ;

	std::vector<int> larger, smaller;
	std::cout << "inside mergeInsertSort" << std::endl;
	std::cout << "given vector is: ";
	for (int num : arr)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	for (size_t i = 0; i + 1 < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
		{
			larger.push_back(arr[i]);
			smaller.push_back(arr[i + 1]);
		}
		else
		{
			larger.push_back(arr[i + 1]);
			smaller.push_back(arr[i]);
		}
	}
	if (arr.size() % 2 != 0)
	{
		larger.push_back(arr.back());
	}
	std::cout << "larger: ";
	for (int num : larger)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	std::cout << "smaller: ";
	for (int num : smaller)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;

	std::cout << "here are the pairs" << std::endl;
	for (int i = 0; i < larger.size(); i++)
	{
		std::cout << larger[i] << " ";
		if (i < smaller.size())
			std::cout << smaller[i] << std::endl;
		else 
			std::cout << std::endl;
	}
	mergeInsertSort(larger);

	for (int num : smaller)
	{
		std::cout << "inside for loop" << std::endl;
		std::cout << "larger vector is: ";
		for (int num : larger)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
		std::cout << "smaller vector is: ";
		for (int num : smaller)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
		binaryInsert(larger, num);
		std::cout << "larger vector after binaryInsert is: ";
		for (int num : larger)
		{
			std::cout << num << " ";
		}
		std::cout << std::endl;
	}
	arr = larger;
}

int main()
{
	std::vector<int> arr = { 5, 3, 2, 1, 4, 6, 7, 8, 9, 10 };
	std::cout << "Before: ";
	for (int num : arr)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	
	mergeInsertSort(arr);

	std::cout << "After: ";
	for (int num : arr)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	return 0;
}