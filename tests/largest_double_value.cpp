/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   largest_double_value.cpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:37:38 by akuburas          #+#    #+#             */
/*   Updated: 2025/01/20 14:38:55 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <cfloat>

int	main(void)
{
	std::cout << "Maximum value for double: " << DBL_MAX << '\n';
	std::cout << "Minimum positive normalized value for double: " << DBL_MIN << '\n';
	std::cout << "Maximum negative value for double: " << -DBL_MAX << '\n';
	std::cout << "Minimum negative normalized value for double: " << -DBL_MIN << '\n';

	return (0);
}
