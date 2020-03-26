#include "iostream"

class test 
{
};

void main() 
{
	int b = 0;
	int* test, *one;

	test = &b;
	one = test;

	std::cout << *test << std::endl;

	b = 1;
	*one = 2;

	std::cout << b << std::endl;

}