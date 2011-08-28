#include <iostream>
#include <cstring>
#include <cerrno>

using namespace std;
#define print(s) std::cout << s << std::endl
#define printx(n) printf("0x%lX\n", n)
typedef unsigned long ulong;
#define FOR(n) for (int i = 0; i < n; ++i)
#define BITS64 0xFFFFFFFFFFFFFFFF

class base5
{
public:

	// string & int2str(long n);
	// long str2int(string & s);
	// unsigned char * decode(long n);
	string decode(ulong n);
	ulong encode(string s);
	string prepare(string s);
	string unprepare(string s);
	base5();
	void debug_string(string s);
	void debug_string_int(string s);
protected:
	string
		table_alpha,
		table_punct,
		table_math,
		table_symb;
	ulong masks[12];
};