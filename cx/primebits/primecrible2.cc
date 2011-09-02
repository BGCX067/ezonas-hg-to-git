#include "primecrible.h"

void Crible :: VariousTests(ulong n, char c)
{
	switch(c)
	{
		case'p': ShowProds(n); break;
		case'g': 
			// ShowPrimes();
			Grow(n); break;
		default: cout << "supply a second argument: <t|g>" << endl;
	}
}

void Crible :: ShowProds(ulong n)
{
	cout << "[PROD] showing 2 * 3 * 5 * 7 * 11 * etc" << endl;
	Pack(n);
	ShowPack(0, n);
	ShowProds(n);
	ulong u = 1;
	for(intg i = 0; i < n and u < ULONG_MAX / 2; ++ i)
	{
		u *= pack[i];
		cout << "2";
		for(intg j = 1; j <= i; ++j)
		cout << " " << pack[j];
		cout << " = " << number_fmt(u) << endl;
	}
	
}

void Crible :: Grow(int density)
{
	cout << "[GROW] counting occurences of numbers being primes "
	 << endl;


	for (intg i = 0, grow_index = 0; (i < size_sieve);)
	{
		for(intg j = 0; j < density; ++ j, ++i)
			if((* crible) [i]) ++ grow_index;
		grow.push_back(grow_index);
		// cout << grow_index << " ";
		grow_index = 0;
	}
	vector<int> diff;
	for(vector<intg>::iterator i = grow.begin() + 1; i < grow.end(); ++ i)
		// cout << *i << " ";
		// diff.push_back(*(i - 1) - * i);
		cout << int(*(i - 1)) - int(* i) << " " << endl;
		// printf("%lu ", * i);
		
	cout  << endl;
}