#include <map>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

void main()
{

	map<string, string*> test_map;

	test_map["��"] = new string("������");
	test_map["��"] = new string("������");

	// Draw �̎���
	for (auto i : test_map) 
	{
		cout << *i.second << endl;
	}

}