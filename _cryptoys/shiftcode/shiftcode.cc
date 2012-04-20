#include "shiftcode.h"
///////////////////////////////////// E N C O D E /////////////////////////////////////
void encode(string plain, int * target)
{
	string enc = "";
	int szz = plain.size();

	int n = num(plain[0]);
	target[0] = num(plain[0]);
	for (int i = 1; i < szz; ++i)
	{
		target[i] = roll(n, num(plain.c_str()[i]));
		n = num(plain.c_str()[i]);
	}
}
///////////////////////////////////// D E C O D E /////////////////////////////////////

string decode(int size, int * code)
{
	string r;
	int n = code[0];
	//cout << n << " = " << chur (n) << endl;
	char c = chur(n);
	r . append (&c, 1);
	//cout << r << endl;
	for (int i = 1; i < size; i++)
	{
		//cout << "code[]=" << code[i] << " n=" << n << endl;
		n = rollout(code[i], n);
		c = chur(n);
		r.append(&c, 1);
		//n = code[i];
	}
	return r;
}
/////// R O L L  &  R O L L O U T
// int roll (char f, char t)

void dec_c(char c)
{
	cout << num(c) << endl;
}
////
void dec_n(int n)
{
	cout << chur(n) << endl;
}
//// ROLL TESTS

void enc_r(char c, char next)
{
	cout << "MODULAR RELATIVE DISTANCE: " << c << " --> " << next << ": "
		<< roll(num(c), num(next)) << " rolls" << endl;
}
////
void dec_r(int last, int n)
{
	cout << "DECODED: " << chur(last) << " + " << n << " rolls: "
	<< chur(rollout(last, n)) << endl;
}

////////////// S H O W  C O D E //////////////

int main()
{
	cout << sz << " symbols, 0-" << sz - 1 << ", "<< string(abt) << endl;

	//for (int i = 0; i < END; ++i)
	//cout << i << " " << chur(i) << " " << num(chur(i)) <<  endl;

	string s = "FUCK YOU AND YOUR JUMBO JUMBO !";
	int a [ s.size() ];
	encode(s, a);
	show_code(a, s.size());
	cout << "decoded: " << 	decode(sizeof(a)/sizeof(int), a) << endl;
// 	int code[] = {10, 1, 0, 1, 1, 1}; // A B B C D E
// 	int szz = 6;
// 	show_code(code, 6);
// 	cout << decode(6, code) << endl;
//
// 	dec_r(10, 10);
// 	dec_r(11, 9);
// 	dec_r(12, 8);
// 	dec_r(13, 7);
// 	enc_r('b', 'a');
// 	enc_r('1', '9');
// 	enc_r('a', 'z');
// 	enc_r('0', 'A');



}

/*
ABC
A11

AZZ
A 25 0

AAA
A00


*/
