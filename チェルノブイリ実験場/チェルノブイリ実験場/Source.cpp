#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void main()
{

	map<string, vector<int*>> test_map;

	test_map["‚ "].push_back(new int(1));
	test_map["‚ "].push_back(new int(10));
	test_map["‚¢"].push_back(new int(2));
	test_map["‚¤"].push_back(new int(3));

#if 1

	string test = "‚ ";
	// Draw ‚ÌŽÀŒ±
	for(auto i: test_map.at(test))
	{
		cout << *i << endl;
	}
#else
	// Update ‚ÌŽÀŒ±
	for(auto i : test_map)
	{
		for (auto j : test_map[i.first])
		{
			cout << *j << endl;
		}
	}
#endif
}