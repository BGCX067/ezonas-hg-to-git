#include "21030.h"

unbase :: unbase() {}
inline string unbase :: tumber30(uint ul)
{
	// DADADADADA
	string str30 = ""; // ADDED
	int down = POWER30; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (30, down)) --down;
	uint r = ul;
	while (down > -1) // loop
	{
		if (ul >= int_pow ((uint)30, down))
		{
			str30 += chr30(r / int_pow(30, down)); //
			r %= int_pow(30, down);
		}
		--down;
	}
	if(str30.length() == 1)
		return " " + str30;
	return str30; // ADDED
	// Don't forget I changed numb to ul !
}
inline string unbase :: tumber36(uint ul)
{
	// DADADADADA
	string str36 = ""; // ADDED
	int down = POWER30; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (36, down)) --down;
	uint r = ul;
	while (down > -1) // loop
	{
		if (ul >= int_pow ((uint)36, down))
		{
			str36 += chr36(r / int_pow(36, down)); //
			r %= int_pow(36, down);
		}
		--down;
	}
	if(str36.length() == 1)
		return " " + str36;
	return str36; // ADDED
	// Don't forget I changed numb to ul !
}
inline uint unbase :: number30(string & str)
{
	uint sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	uint r = 0;	
	for (uint i = 0; i < sz; ++i)
		r += num30(str[i]) * int_pow (30, sz-i-1);
	return r;
}
inline uint unbase :: number36(string & str)
{
	uint sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	uint r = 0;	
	for (uint i = 0; i < sz; ++i)
		r += num36(str[i]) * int_pow (36, sz-i-1);
	return r;
}
inline char unbase :: chr30 (uint n)
{
	if (n < 0 or n > 29) return '_';
	if (n < 10)
		return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}
inline char unbase :: chr36 (uint n)
{
	if (n < 0 or n > 35) return '_';
	if (n < 10)
		return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}
inline uint unbase :: int_pow (uint n, int p)
{
	if (p == 0) return 1;
	uint r = 1;
	for(int i = 0; i < p; ++i) r *= n;
 	return r;
}
void unbase :: show_mult_table30()
{
	cout << "30-based [[0-9][A-T]] multiplication table" << endl << "    ";
	
	for(int i = 1; i < 31; ++i)
	{
		if(i < 10) cout << "  .";
		else cout << " " << i;
	}

	for(int i = 1; i < 31; ++i)
	{
		if(i < 10) cout << endl << "  . ";
		else cout << endl << "(" << i << ")" ;
		
		cout << tumber30(i) << ": ";
		for(int j = 2; j < 31; ++j)
		{
			cout << tumber30(i*j) << " ";		
		}
	}
	cout << endl << "done !" << endl;
}
void unbase :: show_mult_table36()
{
	cout << "36-based [[0-9][A-Z]] multiplication table" << endl << "    ";
	for(int i = 1; i < 37; ++i)
	{
		if(i < 10) cout << "  .";
		else cout << " " << i;
	}

	for(int i = 1; i < 37; ++i)
	{
		if(i < 10) cout << endl << "  . ";
		else cout << endl << "(" << i << ")" ;
		
		cout << tumber36(i) << ": ";
		for(int j = 2; j < 37; ++j)
			cout << tumber36(i*j) << " ";
	}
	cout << endl << "done !" << endl;
}
void unbase :: show30(uint u)
{ cout << u << " -> 30 -> " << tumber30(u) << endl; }
void unbase :: show36(uint u)
{ cout << u << " -> 36 -> " << tumber36(u) << endl; }
void unbase :: show30(string str)
{ cout << str << " -> 30 -> " << number30(str) << endl; }
void unbase :: show36(string str)
{ cout << str << " -> 36 -> " << number36(str) << endl; }
uint unbase :: num30 (char c)
{
	if (c < '0' or c > 'T' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (uint)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (uint)(c - ASC_OFS + 9);
}
uint unbase :: num36 (char c)
{
	if (c < '0' or c > 'Z' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (uint)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (uint)(c - ASC_OFS + 9);
}
