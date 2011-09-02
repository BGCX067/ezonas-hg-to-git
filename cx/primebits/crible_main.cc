#include "primecrible.h"
#include "stdio.h"

int main(int n, char * arg[])
{
	// uint in = 120, l = 80;
	// if (n >= 2) in = strtol(arg[1], NULL, 0);
	// if (n >= 3)  l = strtol(arg[2], NULL, 0);

	// printf("\n☯∫√✕∷≡=∃ ∇∞∵\n");
	printf("\n████████████████████████ √∫ ████████████████████████\n");

	if(n == 3) cout << "bad arguments" << endl;
	if(n == 1)
	{
		cout << "no args given, will use default settings" << endl;
		Crible c(BITS);//, l);
		c.Generate();
		// c.ShowCribleSet();
		// c.Chunkize2();
		// c.WriteFile("output.bit");

		//c.Pack();
		//c.ShowPrimes();
	}
	
	if(n == 2)
	{
		if(arg[1][0] == 'r')
		{
	 		Crible c(BITS);
			// c.ReadFile("output.bit");
		}		
		if(arg[1][0] == 't')
			cout << "supply more arguments for testing" << endl;


		else
		{
			ulong value = strtol(arg[1], 0, 16);
			
			printf("will divide by %lX, resulting sieve limit is %lX\n",
			value, BITS / value);


	 		Crible c(BITS / value);
			c.Generate();
			// c.Pack();
			// c.Chunkize2();
			// c.WriteFile("output.bit");
		}
		
	}
	if(n == 4)
	{
		if(arg[1][0] == 't')
		{
			cout << "performing some tests" << endl;
	 		Crible c(BITS_FAST);
			c.Generate();

			c.VariousTests(ulong(atoi(arg[3])), arg[2][0]);

		}
	}
	return 347;
}



