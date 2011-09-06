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
		cout << "using \"pretty good\" limit" << endl;
		Crible c;//, l);
		c.Generate(BITS_QUICK);

		c.WriteFile("output.bit");

		//c.Pack();
		//c.ShowPrimes();
	}
	
	if(n == 2)
	{
		if(arg[1][0] == 'r')
		{
	 		Crible c;
			c.ReadFile("output.bit");
			// c.ShowCribleSet(0, 100);
			// c.ShowPrimes(0, 100);
			c.ShowPrimes();

		}		
		else if(arg[1][0] == 'h')
		{
	 		Crible c;
			// c.ReadFile("output.bit");
		}		
		else if(arg[1][0] == 't')
		{
			cout << "supply additionnary argument:" << endl;
			cout << "'g' <number>: show growth" << endl;
			cout << "'p': show prime factorial" << endl;
		}
		else
		{
			ulong value = strtol(arg[1], 0, 10);

	 		Crible c;
			c.Generate(value);
			c.ShowPrimes();
			// c.ShowCribleSet(0, value);
			
			c.WriteFile("output.bit");
		}
		
	}
	if(n == 4)
	{
		if(arg[1][0] == 't')
		{
			cout << "performing some tests" << endl;
	 		Crible c;
			c.ReadFile("output.bit");

			c.VariousTests(intg(atoi(arg[3])), arg[2][0]);

		}
	}
//	return 347;
}



