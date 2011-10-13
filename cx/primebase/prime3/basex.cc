#include "basex.h"

basex :: basex() {}
// those conversions are the trickiest
inline string basex :: n2s30(intg ul)
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
inline string basex :: n2s36(intg ul)
{
	// DADADADADA
	string str36 = ""; // ADDED
	int down = POWER30; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (36, down))
		--down;
	intg r = ul;
	
	while (down > -1) // loop
	{
		if (ul >= int_pow ((intg)36, down))
		{
			str36 += chr36(r / int_pow(36, down));
			r %= int_pow(36, down);
		}
		--down;
	}
	if(str36.length() == 1)
		return " " + str36;
	return str36; // ADDED
	// Don't forget I changed numb to ul !
}

// those conversions are the easiest
inline intg basex :: s2n30(string str)
{
	intg sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	intg r = 0;	
	for (intg i = 0; i < sz; ++i)
		r += num30(str[i]) * int_pow (30, sz-i-1);
	return r;
}
inline intg basex :: s2n36(string str)
{
	intg sz = str.length();
	if (str == "0" or sz > POWER30)
	{ cout << "it's NULL" << endl; return 0u; }
	intg r = 0;	
	for (intg i = 0; i < sz; ++i)
		r += num36(str[i]) * int_pow (36, sz-i-1);
	return r;
}

/// accessory functions
inline char basex :: chr30 (intg n)
{
	switch(n)
	{
		// case 0 :
		case 1 : case 2 : case 3 : case 4 : case 5 :
		case 6 : case 7 : case 8 : case 9 :
			return char(n + '0');

		case 10 : case 11 : case 12 : case 13 : case 14 :
		case 15 : case 16 : case 17 : case 18 : case 19 :
		case 20 : case 21 : case 22 : case 23 : case 24 :
		case 25 : case 26 : case 27 : case 28 : case 29 :
		// case 30 : case 31 : case 32 : case 33 : case 34 :
		// case 35 :
			return char('A' + n - 10);
			// return char('A' + n - 10);

		default:
			return '_';
	}
}
inline char basex :: chr36 (intg n)
{
	switch(n)
	{
		// case 0 :
		case 1 : case 2 : case 3 : case 4 : case 5 :
		case 6 : case 7 : case 8 : case 9 :
			return char(n + '0');

		case 10 : case 11 : case 12 : case 13 : case 14 :
		case 15 : case 16 : case 17 : case 18 : case 19 :
		case 20 : case 21 : case 22 : case 23 : case 24 :
		case 25 : case 26 : case 27 : case 28 : case 29 :
		case 30 : case 31 : case 32 : case 33 : case 34 :
		case 35 :
			return char('A' + n - 10);

		default:
			return '_';
	}
}
inline char basex :: chr30_ (intg n)
{
	if (n < 0 or n > 29) return '_';
	if (n < 10)
		return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}
inline char basex :: chr36_ (intg n)
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
		
		cout << n2s30(i) << ": ";
		for(int j = 2; j < 31; ++j)
		{
			cout << n2s30(i*j) << " ";		
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
		
		cout << n2s36(i) << ": ";
		for(int j = 2; j < 37; ++j)
			cout << n2s36(i*j) << " ";
	}
	cout << endl << "done !" << endl;
}
void basex :: show30(intg u) { cout << u << " -> 30 -> " << n2s30(u) << endl; }
void basex :: show36(intg u) { cout << u << " -> 36 -> " << n2s36(u) << endl; }
void basex :: show30(string str) { cout << str << " -> 30 -> " << s2n30(str) << endl; }
void basex :: show36(string str) { cout << str << " -> 36 -> " << s2n36(str) << endl; }
intg basex :: num30_ (char c)
{
	if (c < '0' or c > 'T' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (intg)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (intg)(c - ASC_OFS + 9);
}
intg basex :: num36_ (char c)
{
	if (c < '0' or c > 'Z' or (c > '9' and c < 'A')) return '_';
	if (c < ASC_OFS_N10) return (intg)(c - ASC_OFS_N);
	if (c == '0') return 0;
	return (intg)(c - ASC_OFS + 9);
}
intg basex :: num30 (char c)
{
	switch (c)
	{
		case '0':
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': 
			return c - '0';

		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		// case 'U': case 'V': case 'W': case 'X': case 'Y':
		// case 'Z': 
			return c - '@' + 9;

		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't':
		// case 'u': case 'v': case 'w': case 'x': case 'y':
		// case 'z': 
			return c - '`' + 9;

		default:
			return '_';
	}
}
intg basex :: num36 (char c)
{
	switch (c)
	{
		case '0':
		case '1': case '2': case '3': case '4': case '5':
		case '6': case '7': case '8': case '9': 
			return c - '0';

		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T':
		case 'U': case 'V': case 'W': case 'X': case 'Y':
		case 'Z': 
			return c - '@' + 9;

		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't':
		case 'u': case 'v': case 'w': case 'x': case 'y':
		case 'z': 
			return c - '`' + 9;

		default:
			return '_';
	}
}
