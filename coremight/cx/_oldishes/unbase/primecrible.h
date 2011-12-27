#include <bitset>
#include <iostream>
using namespace std;

//#define CRIBLE_SIZE 0xf0000000
#define CRIBLE_SIZE 0x3ffa000
// 0xf0000000 = 4 026 531 840 = 15·2^31 ///// 4 294 967 296, 2^32
typedef unsigned int uint;

class Crible
{
public:
	Crible(uint n = 100, uint l = 100):
		limit(n),
		count(0u),
		size(CRIBLE_SIZE),
		line_size(l)
	{
		cout << "crible size = " << size << endl;
	}
	
	void Generate();
	void ShowPrimes();
	void ShowPrimes30();
	void ShowPrimes36();
	void ShowArray()
	{
		cout << "\t ";
		for (uint i = 1; i < line_size/10; i += 1)
			cout << "         " << i;
		cout << endl << "\t";
		for (uint i = 0; i < line_size; ++i)
			cout << i % 10;
		for (uint i = 0; i < limit; ++i)
		{
			if (i % line_size == 0) cout << endl << "+"<< i << "\t";
			if (crible[i]) cout << '#';
			else cout << '-';//"·";
		}
		cout << endl;
	}
protected:
	uint limit, count, size, line_size;
	bitset <CRIBLE_SIZE> crible;
};