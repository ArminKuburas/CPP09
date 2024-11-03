/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:30:24 by akuburas          #+#    #+#             */
/*   Updated: 2024/11/03 11:52:52 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <stack>
#include <iostream>
#include <sstream>
#include <stdexcept>

class RPNCalculator
{
	public:
		static int calculate(const std::string &expression);
		RPNCalculator();
		~RPNCalculator();
		RPNCalculator(const RPNCalculator &other);
		RPNCalculator &operator=(const RPNCalculator &other);
		
};