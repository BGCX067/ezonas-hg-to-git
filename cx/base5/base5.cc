#include "base5.h"

base5 :: base5():
	table_alpha(" ABCDEFGHIJKLMNOPQRSTUVWXYZ"),
	table_punct(",.'-^"),
	table_math("+-*/="),
	table_symb("#@&?!")
{
	masks[0]  = 0x0F80000000000000;
	masks[1]  = 0x007C000000000000;
	masks[2]  = 0x0003E00000000000;
	masks[3]  = 0x00001F0000000000;
	masks[4]  = 0x000000F800000000;
	masks[5]  = 0x00000007C0000000;
	masks[6]  = 0x000000003E000000;
	masks[7]  = 0x0000000001F00000;
	masks[8]  = 0x00000000000F8000;
	masks[9]  = 0x0000000000007C00;
	masks[10] = 0x00000000000003E0;
	masks[11] = 0x000000000000001F;

}	

ulong base5 :: encode(string s)
{
	if(s.length() > 12) { cerr << "string too long" << endl; return 0; }
	else if(s.length() < 12)
	{
		int l = s.length();
		// cout << l << endl;
		// s.append(12 - l, ' ')
		s.insert(0, 12 - l, '_');
	}
	// debug_string(s);
	ulong result = 0;

	s = prepare(s);
	for(int i = 0; i < 12; ++ i)
		result |= (ulong(s[i]) << 5 * (11 - i));
	return result;
}

string base5 :: decode(ulong n)
{
	string s(12, 'X');
	
	FOR(12)
		s[i] = char((n & masks [i]) >> 5 * (11 - i));

	// debug_string_int(s);
	return unprepare(s);
}
/* ------------------ translation functions ------------------ */
string base5 :: prepare(string s)
{
	if(s.length() > 12)	{cerr << "string too long" << endl;	return s;}
	// debug_string(s);
	for(int i = 0; i < 12; ++ i)
	{
		if (s[i] > ('A' - 1) and s[i] < ('Z' + 1))		s[i] -= ('A' - 1);
		else if (s[i] > ('a' - 1) and s[i] < ('z' + 1)) s[i] -= ('a' - 1);
		else
			switch (s[i])
			{
				// case ' ':  s[i] = 0; break;
				case '_':  s[i] = 0; break;
				case ',':  s[i] = 27; break;
				case '.':  s[i] = 28; break;
				case '\'': s[i] = 29; break;
				case '-':  s[i] = 30; break;
				case '^':  s[i] = 31; break;

				default:
					cerr << "bad character " << int(s[i]) << endl;
					// debug
					s[i] = 30;
					break;
			}
	}

	// debug_string_int(s);

	return s;
}

string base5 :: unprepare(string s)
{
	if(s.length() > 12) { cerr << "string too long" << endl; return s; }
	// debug_string_int(s);
	for(int i = 0; i < 12; ++ i)
	{
		switch(s[i])
		{
			// case 0:  s[i] = ' '; break;
			case 0:  s[i] = '_'; break;
			case 27: s[i] = table_punct[0]; break;
			case 28: s[i] = table_punct[1]; break;
			case 29: s[i] = table_punct[2]; break;
			case 30: s[i] = table_punct[3]; break;
			case 31: s[i] = table_punct[4]; break;
			default: s[i] += 'A' - 1;
		}
		
	}
	return s;
}
/* ------------------ those are used for debug purposes ------------------ */
void base5 :: debug_string_int(string s)
{
	for(int i = 0; i < 12; ++i)
		cout << int(s[i]) << " ";
	cout << endl;
	
}
void base5 :: debug_string(string s)
{
	cout << s << endl;
	for(int i = 0; i < 12; ++i)
		cout<< int(s[i]) << ":" << s[i]  << " ";
	cout << endl;
}
