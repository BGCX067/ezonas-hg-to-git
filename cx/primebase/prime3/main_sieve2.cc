#include "sieve.h"

int main(int n, char * arg[])
{
	if(n == 2)
	{
		Sieve das;

		das.Generate(2000001);
		das.Pack();
		das.nth_prime(4532);
		das.sum();		
	}
}



