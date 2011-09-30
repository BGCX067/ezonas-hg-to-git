#ifndef Z21030
#define Z21030
#include <string>
#include <iostream>
#include "jokoon.h"
using namespace std;

#define A 'A'
#define Z 'Z'
#define ASC_OFS 64

#define ASC_OFS_N10 58
#define ASC_OFS_N 48

#define POWER30 13
#define ASC_OFS_N10 58
#define ASC_OFS_N 48
#define n2s unbase::tumber27
#define s2n unbase::number27

class unbase
{
	static inline intg num27(char c);
	static inline char chr27(intg num);

	static inline intg num30(char c);
	static inline char chr30(intg num);

	static inline intg num36(char c);
	static inline char chr36(intg num);

public:
	static void dictionnary(string filename);
	static intg int_pow (intg n, int p);

	static string tumber27(intg);
	static intg number27(string );
	static string tumber30(intg ul);
	static string tumber36(intg ul);
	static intg number30(string &);
	static intg number36(string &);
	
	static void show30(intg);
	static void show36(intg);
	static void show30(string);
	static void show36(string);
	
	unbase();
	unbase(intg input);
	unbase(string input, int base);
	
	static void show_mult_table30();
	static void show_mult_table36();
	static void show_mult_table27();
};

#endif // Z21030