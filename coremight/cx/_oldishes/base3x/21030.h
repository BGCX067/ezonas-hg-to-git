#include <string>
#include <iostream>
using namespace std;

#define A 'A'
#define Z 'Z'
#define ASC_OFS 64

#define ASC_OFS_N10 58
#define ASC_OFS_N 48

#define POWER30 13
#define ASC_OFS_N10 58
#define ASC_OFS_N 48

typedef unsigned int uint;
// typedef unsigned long ulong;

class unbase
{
	static inline uint num30(char c);
	static inline char chr30(uint num);

	static inline uint num36(char c);
	static inline char chr36(uint num);

	static inline uint int_pow (uint n, int p);
public:
	static string tumber30(uint ul);
	static string tumber36(uint ul);
	static uint number30(string &);
	static uint number36(string &);
	
	static void show30(uint);
	static void show36(uint);
	static void show30(string);
	static void show36(string);
	
	unbase();
	unbase(uint input);
	unbase(string input, int base);
	
	static void show_mult_table30();
	static void show_mult_table36();
};

