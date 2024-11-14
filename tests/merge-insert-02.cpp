/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge-insert-02.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 12:38:10 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/14 12:44:42 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>

int	main(void)
{
	std::vector<int> arr = { 5, 3, 2, 1, 4, 6, 7, 8, 9, 10 };
	std::cout << "Before: ";
	for (int num : arr)
	{
		std::cout << num << " ";
	}
	std::cout << std::endl;
	
	int straggler;
	if (arr.size() % 2 != 0)
	{
		straggler = arr.back();
		arr.pop_back();
	}
}