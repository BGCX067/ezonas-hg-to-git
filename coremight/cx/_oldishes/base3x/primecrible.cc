#include "primecrible.h"
#include "21030.h"

#include <stdlib.h>
void Crible :: Generate ()
{
	// for(int i = 2; i < limit; ++i) crible[i] = true;
	crible.flip();
	crible[0] = false;
	crible[1] = false;
	for (uint i = 2; i < limit; ++i)
	{
		// if there is a false, loop next (false means i is not prime)
		if(crible[i] == false) continue;
		++ count;
		// zeroes out all numbers from 2*m to n (means here, i is prime)
		for(uint k = 2; i*k < limit; ++k)
			crible[i*k] = false;
	}
}

void Crible :: ShowPrimes()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << (i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
void Crible :: ShowPrimes30()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << unbase :: tumber30(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}void Crible :: ShowPrimes36()
{
	cout << endl;
	for (uint i = 0; i < limit; ++i)
	{
		if (crible[i]) cout << unbase :: tumber36(i) << ' ';
		//else cout << '-';//"·";
	}
	cout << endl;	
}
int main(int n, char * arg[])
{
	// uint in = 120, l = 80;
	// if (n >= 2) in = strtol(arg[1], NULL, 0);
	// if (n >= 3)  l = strtol(arg[2], NULL, 0);

	Crible c(1000);//, l);
	c.Generate();
	//c.ShowArray();
	c.ShowPrimes36();
}