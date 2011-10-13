#include "sieve.h"
#include "basex.h"

#include <stdio.h>

int main(int n, char * arg[])
{
	// uint in = 120, l = 80;
	// if (n >= 2) in = strtol(arg[1], NULL, 0);
	// if (n >= 3)  l = strtol(arg[2], NULL, 0);

	// printf("\n☯∫√✕∷≡=∃ ∇∞∵\n");
	printf("\n████████████████████████ √∫ ████████████████████████\n");

	if(n == 3)
		cout << "bad arguments" << endl;	

	if(n == 1)
	{

		pr("available arguments");
		pr("i\twrite bits into a pbm file");
		pr("r\tread the output.bit file");
		pr("t <g|p|b> n\tproducts, growth or base with n limit");
		// cout << "no args given, will use default settings" << endl;
		// cout << "using \"pretty good\" limit" << endl;
		// Sieve c;//, l);
		// c.Generate(BITS_QUICK*4);
		// c.Generate(BITS_QUICK);

		
		// c.WriteFile("output.bit");

		// c.Pack();
		// c.ShowPack();
		// c.WriteNumbers("NUMBERS.BIT");
		// c.ShowPrimesLine();
	}
	
	if(n == 2)
	{
		if(arg[1][0] == 'r')
		{
	 		Sieve c;
			c.ReadFile("BIGFILES/output.bit");
			c.ShowPrimes();

		}		
		else if(arg[1][0] == 'h')
		{
			pr("available arguments");
			pr("i\twrite bits into a pbm file");
			pr("r\tread the output.bit file");
			pr("t <g|p|b> n\tproducts, growth or base with n limit");
		}		
		else if(arg[1][0] == 't')
		{
			cout << "supply additionnary argument:" << endl;
			cout << "'g' <number>: show growth" << endl;
			cout << "'p': show prime factorial" << endl;
			cout << "'b': show primes in different bases" << endl;
		}
		else if(arg[1][0] == 'i')
		{
			Sieve s;
			s.WritePBM(string("hello.pbm"));
		}


		else
		{
			ulong value = strtol(arg[1], 0, 10);
	 		Sieve c;
			c.Generate(value);
			c.ShowPrimes();
		}
		
	}
	if(n == 4)
	{
		if(arg[1][0] == 't')
		{
			cout << "performing some tests" << endl;
	 		Sieve c;
			int n = atoi(arg[3]);
			switch(arg[2][0])
			{
				case 'p': c.ShowProds(n); 		break;
				case 'g': c.Grow(n); 			break;
				case 'b': c.ShowPrimesBase(n);	break;
				default: cout << "supply a second argument: <t|g|b>" << endl;
			}

		}
	}
//	return 347;
}



