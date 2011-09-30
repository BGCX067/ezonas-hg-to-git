#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
#include <ctime>

#include "jokoon.h"

// #include "21030.h"
using namespace std;

// #define BITS 0x100000UL // mac book pro, 2GB ram: don't go further this value
#define BITS 		0x80000000UL // mac book pro, 2GB ram: don't go further this value
#define BITS_FAST 	0x1000000UL // for fast compile+run
#define BITS_QUICK 	0x10000000UL // for fast compile+run
#define FOR(n) for(int i = 0; i < n; ++ i)
#define Sieve_CHUNK_SIZE 0x1000 // 4ko

#define ULONG_BYTES 8
#define ULONG_BITS 64

#define UINT_BYTES 4
#define UINT_BITS 32

#define INTG_BYTES 4
#define INTG_BITS 32
#define INTG_MAX UINT_MAX


#define str string
// #define Sieve_SIZE 0xF80000 // nothing higher on a 32 bits windows
// #define Sieve_SIZE 0x3000000 // nothing higher on a 64 bits processor

typedef bitset<64> bitset64;
typedef vector<bitset64> :: iterator vect_bs64_iter;
// typedef unsigned int uint;
// typedef unsigned long ulong;
// typedef unsigned int intg;

class Sieve
{
public:
	// Sieve (intg _limit = 100, int _line_size = 100);
	Sieve (int _line_size = 100);
	~ Sieve();
	void Generate(intg);
	string number_fmt(intg n);
	void ShowSieveSet();
	void ShowSieveSet(intg, intg);
	void ShowPrimes(intg a, intg b);
	void ShowPack(intg a = 0, intg b = 0);
	void ShowPrimes();
	void ShowPrimesLine();
	void ShowPrimesBase(int);
	
	void ShowArray();
	void ShowPrimeByPosition(intg i);
	// void ShowPrimes30();
	// void ShowPrimes36();

	bool IsPrime(intg);
	void ReadFile(string); // read ulong array, write into bitset
	void WriteFile(string); // convert bitset into ulong array, writes it
	void WriteNumbers(string);

	void array2bitset();
	// void bitset2bitset64();
	void bitset2array();
	
	void Pack(intg n = 0);
	void VariousTests(intg n, char c);

	void ShowProds(intg n);
	void Grow(int density);
	void HideThis();
	
	
protected:
	size_t
		size_sieve,
		size_array;

	// ulong
	intg
		count,
		* pack,
		* array;

	// int
	// 	line_size,
		// WordSize,
		// NumberOfWords;
	
	bitset<BITS> * Sieve;
	vector <bitset64> Sieve_vect;
	vector<intg> packv, grow;
	// vector <ulong> long_vect;
	// ifstream * in;
	// ofstream * out;
	string filename_input, filename_output;
};

