#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>


// #include "21030.h"
using namespace std;

// #define BITS 0x100000UL // mac book pro, 2GB ram: don't go further this value
#define BITS 0x80000000UL // mac book pro, 2GB ram: don't go further this value
#define BITS_FAST 0x80000000UL / 0x100 // for fast compile+run
#define FOR(n) for(int i = 0; i < n; ++ i)
#define CRIBLE_CHUNK_SIZE 0x1000 // 4ko
#define ULONG_BYTES 8
#define ULONG_BITS 64
#define UINT_BYTES 4
#define UINT_BITS 32
#define str string
// #define CRIBLE_SIZE 0xF80000 // nothing higher on a 32 bits windows
// #define CRIBLE_SIZE 0x3000000 // nothing higher on a 64 bits processor

typedef bitset<64> bitset64;
typedef vector<bitset64> :: iterator vect_bs64_iter;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned int intg;

class Crible
{
public:
	Crible (ulong _limit = 100, int _line_size = 100);
	~ Crible();
	void Generate();
	string number_fmt(ulong n);
	void ShowCribleSet();
	void ShowArray();
	void ShowPrimes(ulong a, ulong b);
	void ShowPack(ulong a = 0, ulong b = 0);
	void ShowPrimes();
	void ShowPrimeByPosition(ulong i);
	// void ShowPrimes30();
	// void ShowPrimes36();

	// void ReadFile(string filename_output);
	// void WriteFile(string);


	void Chunkize();
	void Chunkize2();
	void Pack(ulong n = 0);
	void VariousTests(ulong n, char c);

	void ShowProds(ulong n);
	void Grow(int density);
	void HideThis();
	
protected:
	size_t
		size_sieve,
		size_array;

	// ulong
	uint
		count,
		* pack,
		* array;

	int
		line_size,
		WordSize,
		NumberOfWords;
	
	bitset<BITS> * crible;
	vector <bitset64> crible_vect;
	vector<intg> packv, grow;
	// vector <ulong> long_vect;
	// ifstream * in;
	// ofstream * out;
	string filename_input, filename_output;
};

