#include <string>
#include <vector>
#include <iostream>

using namespace std;

void main()
{
	vector<string> test_vector;
	test_vector.push_back("‚ ‚ ‚ ");
	test_vector.push_back("‚¢‚¢‚¢");
	test_vector.push_back("‚¤‚¤‚¤");
	test_vector.push_back("‚¦‚¦‚¦");

	for (auto i : test_vector)
	{
		cout << i << endl;
	}
}