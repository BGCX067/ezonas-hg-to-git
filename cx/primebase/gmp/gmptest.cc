//#include "gmp.h"
#include <gmp.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include "jokoon.h"

using namespace std;
#define p(s) printf("%s\n", s);

int main()
{
	// mpz_t x, y, z;
	mpz_t x;
	mpz_init (x);
	int base = 62;
	
	char LOLPHABET[] =
	"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	// char LOLPHABET[] =
	// "_ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	printf("%d\n", (int)strlen(LOLPHABET));
	char cc[2]; cc[0] = '0'; cc[1] = '\0';
	printf("%s\n", cc);
	
	FOR(62)
	{
		if((i % 5)== 0) printf ("\n");
		cc[0] = LOLPHABET[i];
		printf("%s = ", cc);
		mpz_set_str(x, cc, base);
		gmp_printf("%Zd, ", x);
	}
	printf("\n---\n");
	
	
	// int base = 16;
	// string number("100");
	// mpz_set_str(x, number.c_str(), base);
	// 
	// gmp_printf("%Zd\n", x);
	// FOR(0x1000)
	// {
	// 	number += "0";
	// 	mpz_set_str(x, number.c_str(), base);
	// 	// gmp_printf("%Zd\n", x);
	// }
	// // gmp_printf("%Zd\n", x);
	// // pr(mpz_get_str(NULL, 62, x));
	// map <int, int> m;
	// for(int i = 2; i <= 62; ++i)
	// {
	// 	
	// 	m [i] = string(mpz_get_str(NULL, i, x)).length();
	// }
	// for(int i = 2; i <= 62; ++i)
	// 	cout << i << " " << m[i] << endl;


	// pvar("_mp_size", x._mp_size);
	// pvar("_mp_d", x._mp_d);
	// pvar("_mp_alloc", x._mp_alloc);
	// gmp_printf ("%Zd\n", x);
	// mpz_nextprime(y, x);
	// gmp_printf ("%Zd\n", y);
	// gmp_printf ("%Zd\n", z);

// 	switch(mpz_probab_prime_p(z, 1))
// 	{
// 		case 0: p("sorry"); break;
// 		case 1: p("maybe"); break;
// 		case 2: p("yup"); break;
// 	}

}

/*
-lgmp
-lgmpxx
*/
