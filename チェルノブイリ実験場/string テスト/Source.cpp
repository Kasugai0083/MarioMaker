#include <iostream>
#include <string>

void main()
{
	std::string test = "‚ ‚ ‚ ";

	float val = 100;

	test += std::to_string(val);

	std::cout << test.c_str() << std::endl;
}