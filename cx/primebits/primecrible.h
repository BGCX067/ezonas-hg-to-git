#include <bitset>
#include <iostream>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;
#include "21030.h"

// #define BITS 0xF000000000000000
// #define BITS 0xF00000000000
// #define BITS 0x100000000
			 // 4294967296
//			 16777216
#define BITS 100000000

#define CRIBLE_CHUNK_SIZE 0x1000 // 4ko
#define ULONG_BYTES 8
#define ULONG_BITS 64

// #define CRIBLE_SIZE 0xF80000 // nothing higher on a 32 bits windows
// #define CRIBLE_SIZE 0x3000000 // nothing higher on a 64 bits processor
// 0xf0000000 = 4 026 531 840 = 15·2^31 ///// 4 294 967 296, 2^32
// #define SIZE 0x80000000
// #define WORD_SIZE 64
// #define SIZE 64

typedef bitset<64> bitset64;
typedef vector<bitset64> :: iterator vect_bs64_iter;
typedef unsigned int uint;
typedef unsigned long ulong;
// typedef vector < bitset <SIZE> > word_vect;
// typedef word_vect :: iterator word_vect_iter;


class Crible
{
public:
	Crible (ulong _limit = 100, int _line_size = 100,
		string filename_i = "intput.bits",
		string filename_o = "output.bits");
	~ Crible();
	void Generate();
	void ShowPrimes(ulong a, ulong b);
	void ShowPack(ulong a, ulong b);
	void ShowPrimes();
	void ShowPrimes30();
	void ShowPrimes36();
	void ShowArray();
	void ReadFile();
	void WriteFile();
	void ShowCribleSet();
	// void OpenFiles();
	// void CloseFiles();
	void ShowPrimeByPosition(ulong i);
	void ChunkizeCrible();
	void Pack();
	// void Densify()
	// {
	// 	// ?
	// }
	
protected:
	ulong
		limit,
		count,
		buffer,
		size,
		* pack;

	int
		line_size,
		WordSize,
		NumberOfWords;
	
	bitset<BITS> * crible;
	vector <bitset64> crible_vect;
	// vector <ulong> long_vect;
	ifstream * in;
	ofstream * out;
};

