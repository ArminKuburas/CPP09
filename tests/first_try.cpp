/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_try.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:49:54 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/27 20:01:40 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <optional>
#include <variant>

using variant_t = std::variant<vector<int>, vector<pair<int, int>>, vector>;

void pair_up(arr)
{
	std::optional<int> leftover;
	if (arr.size() % 2 != 0)
	{
		leftover = arr.back();
		arr.pop_back();
	}
	std::vector<std::pair<int, int>> pairs;
	
}

int	main(void)
{
	std::vector<int> arr = { 5, 3, 2, 1, 4, 6, 7, 8, 9, 10, 0 };
	pair_up(arr);
}
	