#include <iostream>
#include <string>
#include <functional>
#include "hashTable.h"

using namespace std;

int simplePolynomialHash(string& str)
{
	unsigned long long sum = 0;
	unsigned long long x = 263;
	unsigned long long xInPower = 1;
	unsigned long long p = 1000000007;
	for (int i = 0; i < str.size(); ++i)
	{
		sum = (((str[i] * xInPower) % p) + sum) % p;
		xInPower = (xInPower * x) % p;
	}
	return sum;
}

int main()
{
	/* example program
	input:
		enter size of hash table
		enter amount of commands
		enter commands
	output:
		results of commands
	*/
	int size, n;
	cin >> size >> n;
	hashTable<string> ht(size, ptr_fun(simplePolynomialHash));
	for (int i = 0; i < n; ++i)
	{
		string command;
		cin >> command;
		if (command == "check") // print chain number
		{
			int x;
			cin >> x;
			string result;
			for (auto it = ht.chain(x).begin(); it != ht.chain(x).end(); ++it)
				result += *it + " ";
			cout << result << endl;
		}
		else
		{
			string str;
			cin >> str;
			if (command == "add")
			{
				ht.add(str);
			}
			else if (command == "find")
			{
				auto it = ht.find(str);
				if (it._Ptr != nullptr)
					cout << "yes" << endl;
				else
					cout << "no" << endl;
			}
			else if (command == "del") // delete
			{ 
				ht.remove(str);
			}
		}
	}
	return 0;
}