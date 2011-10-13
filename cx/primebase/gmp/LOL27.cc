#include <gmpxx.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

#include "jokoon.h"
using namespace std;

inline char trnsl2chr(char c)
{
	switch(c)
	{
		// case ' ': case '_': case '0': return '_';
		case '1': 			return 'A';
		case '2': 			return 'B';
		case '3': 			return 'C';
		case '4': 			return 'D';
		case '5': 			return 'E';
		case '6': 			return 'F';
		case '7': 			return 'G';
		case '8': 			return 'H';
		case '9': 			return 'I';
		case 'a': case 'A': return 'J';
		case 'b': case 'B': return 'K';
		case 'c': case 'C': return 'L';
		case 'd': case 'D': return 'M';
		case 'e': case 'E': return 'N';
		case 'f': case 'F': return 'O';
		case 'g': case 'G': return 'P';
		case 'h': case 'H': return 'Q';
		case 'i': case 'I': return 'R';
		case 'j': case 'J': return 'S';
		case 'k': case 'K': return 'T';
		case 'l': case 'L': return 'U';
		case 'm': case 'M': return 'V';
		case 'n': case 'N': return 'W';
		case 'o': case 'O': return 'X';
		case 'p': case 'P': return 'Y';
		case 'q': case 'Q': return 'Z';

		default: return '_';
	}
}
inline char trnsl2gmp(char c)
{
	switch(c)
	{
	// case ' ': case '_': case '0': return '0';
	case 'a': case 'A': return '1';
	case 'b': case 'B': return '2';
	case 'c': case 'C': return '3';
	case 'd': case 'D': return '4';
	case 'e': case 'E': return '5';
	case 'f': case 'F': return '6';
	case 'g': case 'G': return '7';
	case 'h': case 'H': return '8';
	case 'i': case 'I': return '9';
	case 'j': case 'J': return 'A';
	case 'k': case 'K': return 'B';
	case 'l': case 'L': return 'C';
	case 'm': case 'M': return 'D';
	case 'n': case 'N': return 'E';
	case 'o': case 'O': return 'F';
	case 'p': case 'P': return 'G';
	case 'q': case 'Q': return 'H';
	case 'r': case 'R': return 'I';
	case 's': case 'S': return 'J';
	case 't': case 'T': return 'K';
	case 'u': case 'U': return 'L';
	case 'v': case 'V': return 'M';
	case 'w': case 'W': return 'N';
	case 'x': case 'X': return 'O';
	case 'y': case 'Y': return 'P';
	case 'z': case 'Z': return 'Q';
	
	default: return '0';
	}
}
// string mpz2str (mpz_class a)
// {
// 	string s(a.get_str(27));	
// 	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
// 		(*itr) = trnsl2chr(* itr);
// 	return s;
// }
// mpz_class str2mpz (string s)
// {
// 	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
// 		(*itr) = trnsl2gmp(* itr);
// 	mpz_class a;// mpz_init (a);
// 	a.set_str(s, 27);
// 	return a;
// }
// omly string (mpz probab prime has no c++ binding)
string mpz2str (string s) // [0-9][A-Z] -> 0[AZ]
{
	// string s(a.get_str(27));	
	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
		(*itr) = trnsl2chr(* itr);
	return s;
}
string str2mpz (string s)
{
	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
		(*itr) = trnsl2gmp(* itr);
	mpz_class a;// mpz_init (a);
	return s;
}


int main()
{
	ifstream dict("words-nix");
	// ifstream dict(filename.c_str(),ifstream::in );
	if(dict.is_open())
	{
		string line;
		vector<string> lines;
		vector<string> lines13;
		while (dict.good())
		{
			getline (dict, line);
			if (line.length() > 13)
				lines13.push_back(line);
			else
				lines.push_back(line);
			
		}
	
		mpz_t a;
		mpz_init(a);
	
		FOR_ITR(string, lines)
		{
			mpz_set_str(a, str2mpz(* itr).c_str(), 27);
			switch(mpz_probab_prime_p(a, 2))
			{
				case 0:
					break;
				// case 1:
				// 	cout << (* itr) << " (MAYBE)" << endl;
				// 	break;
				case 2:
					cout << (* itr) << endl;
					break;
			}
		}
		dict.close();
	}
	else
		pr("dict file not opened");
	// pr(str2mpz("0"));
	// pr(str2mpz("a"));
	// pr(str2mpz("b"));
	// pr(str2mpz("z"));
	// pr(str2mpz("a0"));
	// 
	// pr(mpz2str("10"));
	
}