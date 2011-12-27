#include "sieve.h"
#include "basex.h"
#include "jokoon.h"



int main(int n, char * arg[])
{
	if(n == 0)
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
	
	pr(basex::s2n27("_"));
	pr(basex::s2n27("0"));
	pr(basex::s2n27(" "));
	pr(basex::s2n27("a"));
	pr(basex::s2n27("b"));
	pr(basex::s2n27("z"));
	pr(basex::s2n27("a0"));
	pr(basex::s2n27("aa"));
	
	pr(basex::s2n27("zz"));
	pr(basex::s2n27("a00"));
	pr(basex::s2n27("zzz"));
	pr(basex::s2n27("a000"));
	pr(basex::s2n27("zzzz"));
	pr(basex::s2n27("a0000"));
}