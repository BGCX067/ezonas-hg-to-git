#include "primewords.h"
// after !


////// ==== POP_LIST ==== //////

string workode :: tumber(ulong ul)
{
	// DADADADADA
	string str36 = ""; // ADDED
	int down = POWER36; // oddly it's the same as 27, check sizepower.py
	while (ul > int_pow (36, down)) --down;
	ulong r = ul;
	while (down > -1) // loop
	{
		//cout << "track: "<< str36 << " " << r << endl;
		if (ul >= int_pow ((ulong)36, down))
		{
			str36 += chr36(r / int_pow(36, down)); //
			r %= int_pow(36, down);
			//cout << "track: "<< str36 << " " << r << endl;

		}
		//else str36 += '0';
		--down;
	}
	return str36; // ADDED
	// Don't forget I changed numb to ul !
}

char workode :: chr36 (ulong n)
{
	if (n < 0 or n > 35) return '_';
	if (n < 10) return (char)(n + ASC_OFS_N);
	return (char)(n + ASC_OFS - 9);
}

ulong workode :: int_pow (ulong n, int p)
{
	if (p == 0) return 1;
	//cout << n << " " << p << endl;
	ulong r = 1;
	for(int i = 0; i < p; ++i) r *= n;
 	return r;
}


void workode :: pop_list(int r = 10)
{
	cout << r << " columns by row..." << endl;
	printf ("√ø ∫Ω\t");
	for(int i = 1; i <= r; ++i) cout << "c:" << i << "\t";
	for(int i = 0; i < count; ++i)
	{
// 		if(not (i % r)) cout << endl << "r:" << i/10 << "\t";
		if(not (i % r)) cout << endl ;
// 		cout << primes[i] << "\t";
		cout << tumber(primes[i]) << "\t";
	}

	cout << endl << "#eoli" << endl;
}



void workode :: show ()
{
	if (count != 0)
	pop_list(20);
	else
	cout << "No loaded/generated data to print !" << endl;
}