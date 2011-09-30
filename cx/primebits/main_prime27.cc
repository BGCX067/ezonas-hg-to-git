#include "sieve.h"
#include "basex.h"
#include "jokoon.h"



int main(int n, char * arg[])
{
	if(n == 1)
	{
		Sieve c;
		// c.Generate(BITS_QUICK);

		c.ReadFile("BIGFILES/output.bit");
		
		ifstream dict("BIGFILES/words-nix");
		string s;
		int i = 0;
		if (dict.is_open())
		{
			while (not dict.eof())
			{
				dict >> s;
				if(c.IsPrime(basex::s2n27(s))) pr(s);
			}
			// for(int j = 0; j < s.length(); ++j)
			// 	pr(int(s[j]));
		}
		dict.close();
	}

	if(n == 2)
	{
	}
}