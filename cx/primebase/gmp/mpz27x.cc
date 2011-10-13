#include <gmpxx.h>
#include <stdio.h>
#include <iostream>
#include <map>
// #include <regex>
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
// int set_str(const char *s, int base)
// int set_str(const std::string &s, int base)
// std::string get_str(int base = 10) const
string mpz2str (mpz_class a)
{
	// string s(mpz_get_str(NULL, 27, a));
	string s(a.get_str(27));
	
	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
		(*itr) = trnsl2chr(* itr);
	return s;
}
mpz_class str2mpz (string s)
{
	for(string::iterator itr = s.begin(); itr != s.end(); ++ itr)
		(*itr) = trnsl2gmp(* itr);
	mpz_class a;// mpz_init (a);
	a.set_str(s, 27);
	return a;
}
// string format(string s, string search, char * replace)
string format(string s, string search, string replace)
{
	// s.replace(s.find(search), search.length(), replace.c_str());
	int n = 0;
	while ((n = s.find(search)) != -1)
		s.replace(n, search.length(), replace.c_str());
		// s.replace(n, search.length(), string(replace).c_str());
	
	return s;
}

// string preformat(string s)
// {
// 	string r = (format(s, string("beige"), string("pink")));
// 
// 	// r = (format(s, string("\n"),  string("__")));			s = r;
// 	r = (format(s, string(" "), string("_")));   		s = r;
// 
// 	r = (format(s, string("."), string("___"))); 			s = r;
// 	r = (format(s, string(","), string("__")));  			s = r;
// 
// 	return r;
// }
// 
// string unformat(string s)
// {
// 	string r;
// 	r = (format(s, string("_"),    string(" ")));   		s = r;
// 	r = (format(s, string("I_M"),  string("I'M"))); 		s = r;
// 	r = (format(s, string("___"),  string(". ")));   		s = r;
// 	r = (format(s, string("__"),   string(", ")));   		s = r;
// 	
// 	
// 	// r = (format(s, string("__"), string("\n")));  		s = r;
// 	return r;
// }

int main()
{
	string s("Hello I'm nafnaf I'm a cat, I'm beige, and I have a brother named dandan, and he is also beige.\nI like tuna, brocolis and bananas.");
	cout << s << endl;
	cout << (mpz2str(str2mpz((s)))) << endl;
	
	// cout << s2 << endl;
	// string s2(format(s, string("beige"), string("pink")));
	// string s2(format(s, string("beige"), string("pink")));
	// cout << format(s, string("beige"), string("pink")) << endl;
	// cout << s2 << endl;
// 	string s3(
// 	/*
// "Monsieur,\
// \
// Ayant vu votre offre d'emploi sur le site de pole emploi dont le\
// numero d'offre est le 387389R, je vous propose donc ma candidature a\
// cet emploi.\
// \
// Autodidacte depuis toujours mes competences en informatique sont assez\
// vastes. Curieux, volontaire et reflechi je saurai appliquer ces\
// qualites pour integrer votre equipe.\
// \
// Vous trouverez ci-joint mon C.V, je reste a votre disposition pour\
// tout renseignement complementaire.\
// \
// Dans l'attente, je vous prie d'agreer, Monsieur, mes respectueuses salutations."
// */
// 	);
}