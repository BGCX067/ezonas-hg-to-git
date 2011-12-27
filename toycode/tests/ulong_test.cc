#include <iostream>
#include <stdio.h>
#include <bitset>
#include <vector>
using namespace std;

typedef bitset<64> bitset64;


int main()
{
	// cout << sizeof(unsigned long long) << endl;
	// cout << sizeof(unsigned long) << endl;
	// cout << sizeof(unsigned int) << endl;
	vector <bitset64> vset;

	vset.push_back(bitset64(0x6c7fdea));
	vset.push_back(bitset64(0x9eafcec));
	vset.push_back(bitset64(0xbabd543));
	// cout << vset[0].to_ulong() << endl;
	// vset.at(0).set();
	// cout << vset[0].to_ulong() << endl;
	// cout << set[0].to_ulong() + 1 << endl;
	
	// vset[2432u][42432] = set[54453543];
	return 347;
}