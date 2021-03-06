#include "basex.h"
#include <vector>
#include <fstream>


inline intg basex :: num27(char c)
{
	switch(c)
	{
	case '_':
	case ' ':
	case '0':
		return 0;
		
	case 'A': case 'B': case 'C': case 'D':
	case 'E': case 'F': case 'G': case 'H':
	case 'I': case 'J': case 'K': case 'L':
	case 'M': case 'N': case 'O': case 'P':
	case 'Q': case 'R': case 'S': case 'T':
	case 'U': case 'V': case 'W': case 'X':
	case 'Y': case 'Z':
		return c - '@';

	case 'a': case 'b': case 'c': case 'd':
	case 'e': case 'f': case 'g': case 'h':
 	case 'i': case 'j': case 'k': case 'l':
	case 'm': case 'n': case 'o': case 'p':
	case 'q': case 'r': case 's': case 't':
	case 'u': case 'v': case 'w': case 'x':
	case 'y': case 'z':
		return c - '`';

		default: return 0;
	}
}

inline char basex :: chr27(intg num)
{
	// if((num < 1 or num > 26) ) return '_';
	switch(num)
	{
		case 1:  case 2:  case 3:  case 4:  case 5:
		case 6:  case 7:  case 8:  case 9:  case 10:
		case 11: case 12: case 13: case 14: case 15:
		case 16: case 17: case 18: case 19: case 20:
		case 21: case 22: case 23: case 24: case 25:
		case 26:
		
		return num + '@';
		default: return '_';
	}
}

intg basex :: s2n27(string str)
{
	intg sz = str.length();
	if (str == "0")
		return 0;
	
 	if(sz > 13)
	// { return basex::int_pow(27,13)-1; }
	{ return 0; }
	intg r = 0;	
	for (intg i = 0; i < sz; ++i)
		r += num27(str[i]) * int_pow (27, sz-i-1);
	return r;
	
}

string basex :: n2s27(intg ul)
{
	// DADADADADA
	if(ul == 0) return string("_");
	string str27 = ""; // ADDED
	if(ul > int_pow(27, 13))
	{
		pr("BAD NUMBER !");
		return string("ZZZZZZZZZZZZZ");
	}

	int down = 13; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (27, down)) --down;
	intg r = ul;
	while (down > -1) // loop
	{
		if (ul >= int_pow (27u, down))
		{
			str27 += chr27(r / int_pow(27, down)); //
			r %= int_pow(27, down);
		}
		--down;
	}
	if(str27.length() == 1)
		return "_" + str27;
	return str27; // ADDED
	// Don't forget I changed numb to ul !
	
}

void basex :: show_mult_table27()
{
	cout << "27-based [A-Z] multiplication table" << endl << "   ";
	for(int i = 1; i < 27; ++i)
		cout << "  " << char(i+'@');

	for(int i = 1; i < 27; ++i)
	{
		cout << endl;
		
		cout << n2s27(i) << ": ";
		for(int j = 2; j < 28; ++j)
			cout << n2s27(i*j) << " ";
	}
	cout << endl << "done !" << endl;
}

void basex :: dictionnary(string filename)
{
	// ifstream dict("words-nix");
	ifstream dict(filename.c_str(),ifstream::in );
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
		dict.close();
		// FOR_ITR(string, lines)
		// 	cout << (* itr ) << " " << itr ->length() << endl;
		// FOR_ITR(string, lines13)
		// 	cout << (* itr ) << " " << itr ->length() << endl;
		cout << "13 chars or less: "<< lines.size() << endl;
		cout << "14 chars or more: "<< lines13.size() << endl;
		cout << "14 chars or more: "<< lines13.size() << endl;
		FOR_ITR(string, lines)
			cout << itr ->length() << " " << (* itr ) << " " << s2n27(*itr) << endl;
	}
	else
		pr("dict file not opened");
	
}
















/**/