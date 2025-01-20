/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akuburas <akuburas@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 11:51:15 by akuburas          #+#    #+#             */
/*   Updated: 2025/01/20 14:57:48 by akuburas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int RPNCalculator::calculate(const std::string &expression)
{
	std::stack<int> stack;
	std::istringstream iss(expression);
	std::string token;

	while (iss >> token)
	{
		if (token == "+" || token == "-" || token == "*" || token == "/")
		{
			if (stack.size() < 2)
				throw std::runtime_error("Error: insufficient operands for operation");
			int a = stack.top();
			stack.pop();
			int b = stack.top();
			stack.pop();
			int result = 0;

			if (token == "+")
				result = b + a;
			else if (token == "-")
				result = b - a;
			else if (token == "*")
				result = b * a;
			else if (token == "/")
			{
				if (a == 0)
					throw std::runtime_error("Error: division by zero");
				result = b / a;
			}
			stack.push(result);
		}
		else if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-' && isdigit(token[1])))
		{
			bool isValid = true;
			for (size_t i = 1; i < token.size(); i++)
			{
				if (!isdigit(token[i]))
				{
					isValid = false;
					break;
				}
			}
			if (isValid)
				stack.push(std::stoi(token));
			else
				throw std::runtime_error("Error: invalid token");
		}
		else if (token[0] == '(')
			throw std::runtime_error("Error");
		else
			throw std::runtime_error("Error: invalid token");
	}
	if (stack.size() != 1)
		throw std::runtime_error("Error: insufficient operators for operation");
	return (stack.top());	
}

RPNCalculator::RPNCalculator()
{
}

RPNCalculator::~RPNCalculator()
{
}

RPNCalculator::RPNCalculator(const RPNCalculator &other)
{
	(void)other;
}

RPNCalculator &RPNCalculator::operator=(const RPNCalculator &other)
{
	(void)other;
	return (*this);
}