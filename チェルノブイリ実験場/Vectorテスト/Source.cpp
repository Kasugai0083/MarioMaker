#include <string>
#include <vector>
#include <iostream>

using namespace std;

void main()
{
	vector<string> test_vector;
	test_vector.push_back("あああ");
	test_vector.push_back("いいい");
	test_vector.push_back("ううう");
	test_vector.push_back("えええ");

	for (auto i : test_vector)
	{
		cout << i << endl;
	}
}