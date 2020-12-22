#include <iostream>
#include <string>
#include "calc.h"

int main (int argc, char **argv)
{
	std::string exp;
	std::getline(std::cin, exp);
	std::cout << calc(exp) << std::endl;

	return 0;
}
