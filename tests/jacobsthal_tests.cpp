#include <cmath>
#include <iostream>

long _jacobsthal_number(long n)
{
	int return_number = round((pow(2, n + 2) - pow(-1, n + 2)) / 3);
	return return_number;
}

int main()
{
	int n = 1;
	std::cout << "Jacobsthal number for n = " << n << " is " << _jacobsthal_number(n) << std::endl;
	return 0;
}