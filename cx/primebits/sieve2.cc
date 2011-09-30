#include "sieve.h"

void Sieve :: VariousTests(intg n, char c)
{
}

void Sieve :: ShowProds(intg n)
{
	cout << "[PROD] showing 2 * 3 * 5 * 7 * 11 * etc" << endl;
	Pack(n);
	ShowPack(0, n);
	ShowProds(n);
	intg u = 1;
	for(intg i = 0; i < n and u < INTG_MAX / 2; ++ i)
	{
		u *= pack[i];
		cout << "2";
		for(intg j = 1; j <= i; ++j)
		cout << " " << pack[j];
		cout << " = " << number_fmt(u) << endl;
	}
	
}

void Sieve :: Grow(int density)
{
	
	intg slice = size_sieve / density + 1;
	cout
		<< endl << "[GROW] showing how many primes there are every each "
		<< slice << " number" << endl;
	intg largest = 0, smallest = 0;
	for (intg i = 0, grow_index = 0; i < size_sieve;)
	{
		for(intg j = 0; j < slice and (i < size_sieve); ++ j, ++i)
			if((* databits) [i]) ++ grow_index;
		
		if(grow_index > largest)
			largest = grow_index;
		if(grow_index < smallest or smallest == 0)
			smallest = grow_index;
		
		grow.push_back(grow_index);
		grow_index = 0;
	}
	int j = 0;
	cout << "largest: " << largest << endl
		<< "smallest: " << smallest << endl;

	// for(vector<intg>::iterator i = grow.begin(); i < grow.end(); ++ i, ++ j)
	// 	cout << *i << " ";
	// cout  << endl;

	for(vector<intg>::iterator i = grow.begin(); i < grow.end(); ++ i, ++ j)
		// cout << 100.0 * float(*i) / float(slice) << " ";
		printf("%.2f ", 100.0 * float(*i) / float(slice));// << " ";
	cout  << endl;
}

bool Sieve :: IsPrime(intg i)
{
	if(i > size_sieve)
	{
		cerr<<"number queried too large, maximum is "<<size_sieve<<endl;
		return false;
	}
	return (*databits)[i];
}
