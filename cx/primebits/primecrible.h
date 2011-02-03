#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
#include "21030.h"

//#define CRIBLE_SIZE 0xf0000000
// #define CRIBLE_SIZE 0x3ffa000
#define CRIBLE_SIZE 0xF80000 // nothing higher on a 32 bits windows
// 0xf0000000 = 4 026 531 840 = 15·2^31 ///// 4 294 967 296, 2^32
typedef unsigned int uint;
// #define SIZE 0x80000000
#define WORD_SIZE 64
#define SIZE 64

typedef unsigned long ulong;
typedef vector < bitset <SIZE> > word_vect;
typedef word_vect :: iterator word_vect_iter;


class Crible
{
public:
	Crible (uint n = 100, uint l = 100,
		string filename_i = "intput.bi",
		string filename_o = "output.bi");
	~ Crible();
	void Generate();
	void ShowPrimes(int a, int b);
	void ShowPack(int a, int b);
	void ShowPrimes();
	void ShowPrimes30();
	void ShowPrimes36();
	void ShowArray();
	void ReadFile();
	void WriteFile();
	void Show();
	void ShowPrimeByPosition(int i);

	void Densify()
	{
		// ?
	}
	
	void Pack();
protected:
	uint
		limit,
		count,
		size,
		line_size;
	
	bitset <CRIBLE_SIZE> crible;
	ifstream * in;
	ofstream * out;
	// bitset <SIZE> crible;
	vector <bitset <SIZE> > vcrible; // unused, I will implement files LATER
	int WordSize;
	int NumberOfWords;
	ulong buffer;
	uint * pack;

};
