#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void main()
{

	map<string, string*> test_map;

	test_map["あ"] = new string("あああ");
	test_map["い"] = new string("いいい");

	// Draw の実験
	for (auto i : test_map) 
	{
		cout << *i.second << endl;
	}

}