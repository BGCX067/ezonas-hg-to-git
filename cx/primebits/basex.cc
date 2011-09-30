#include "basex.h"

basex :: basex() {}
inline string basex :: tumber30(intg ul)
{
	// DADADADADA
	string str30 = ""; // ADDED
	int down = POWER30; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (30, down)) --down;
	intg r = ul;
	while (down > -1) // loop
	{
		if (ul >= int_pow ((intg)30, down))
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
inline string basex :: tumber36(intg ul)
{
	// DADADADADA
	string str36 = ""; // ADDED
	int down = POWER30; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (36, down)) --down;
	intg r = ul;
	while (down > -1) // loop
	{
		if (ul >= int_pow ((intg)36, down))
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
inline intg basex :: number30(string & str)
{
	intg sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	intg r = 0;	
	for (intg i = 0; i < sz; ++i)
		r += num30(str[i]) * int_pow (30, sz-i-1);
	return r;
}
inline intg basex :: number36(string & str)
{
	intg sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	intg r = 0;	
	for (intg i = 0; i < sz; ++i)
		r += num36(str[i]) * int_pow (36, sz-i-1);
	return r;
}
inline char basex :: chr30 (intg n)
{
	if (n < 0 or n > 29) return '_';
	if (n < 10)
		return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}
inline char basex :: chr36 (intg n)
{
	if (n < 0 or n > 35) return '_';
	if (n < 10)
		return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}
inline intg basex :: int_pow (intg n, int p)
{
	if (p == 0) return 1;
	intg r = 1;
	for(int i = 0; i < p; ++i) r *= n;
 	return r;
}
void basex :: show_mult_table30()
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
void basex :: show_mult_table36()
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
void basex :: show30(intg u)
{ cout << u << " -> 30 -> " << tumber30(u) << endl; }
void basex :: show36(intg u)
{ cout << u << " -> 36 -> " << tumber36(u) << endl; }
void basex :: show30(string str)
{ cout << str << " -> 30 -> " << number30(str) << endl; }
void basex :: show36(string str)
{ cout << str << " -> 36 -> " << number36(str) << endl; }
intg basex :: num30 (char c)
{
	if (c < '0' or c > 'T' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (intg)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (intg)(c - ASC_OFS + 9);
}
intg basex :: num36 (char c)
{
	if (c < '0' or c > 'Z' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (intg)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (intg)(c - ASC_OFS + 9);
}
