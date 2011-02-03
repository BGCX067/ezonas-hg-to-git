#include "primecrible.h"
#include "stdio.h"

int main(int n, char * arg[])
{
	// uint in = 120, l = 80;
	// if (n >= 2) in = strtol(arg[1], NULL, 0);
	// if (n >= 3)  l = strtol(arg[2], NULL, 0);

	Crible c(10000000);//, l);
	c.Generate();
	c.Pack();
	//c.ShowPrimes();
	
	//c.ShowPrimeByPosition(10001);
	//c.ShowArray();
	// c.ShowPrimes36();
//	system("pause");
    //cin.get();
	// return 0xdeadbeef;
	
	c.ShowPrimes();
	return 0;

}

