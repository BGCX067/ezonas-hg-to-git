#include "basex.h"
#include <gmpxx.h>
number basex :: z(intg n, unsigned int base)
{
	number r;
	int exponent = 10;
	pr("hello to universal base conversion");
	while (n > int_pow (base, exponent))
	{
		-- exponent;
		p(exponent)<<" ";
	}
	p("base = ") << exponent << endl;
	intg rest = n;
	while (exponent >= 0) // loop
	{
		if (n >= int_pow ((intg)base, exponent))
		{
			// strbase += chrbase(r / int_pow(base, exponent)); //
			unsigned int f = rest / int_pow(base, exponent);
			// pr_(f);
			r.push_back(f);
			rest %= int_pow(base, exponent);
		}
		-- exponent;
	}
	// if(strbase.length() == 1)
	// 	return " " + strbase;
	return r; // ADDED
}
number basex :: z(mpz_t n, unsigned int base)
{
	number r;
	int exponent = 100;
	pr("hello to universal base conversion");
	// while (n > int_pow (base, exponent))
	while (n > int_pow (base, exponent))
	{
		-- exponent;
		p(exponent)<<" ";
	}
	p("base = ") << exponent << endl;
	intg rest = n;
	while (exponent >= 0) // loop
	{
		if (n >= int_pow ((intg)base, exponent))
		{
			// strbase += chrbase(r / int_pow(base, exponent)); //
			unsigned int f = rest / int_pow(base, exponent);
			// pr_(f);
			r.push_back(f);
			rest %= int_pow(base, exponent);
		}
		-- exponent;
	}
	// if(strbase.length() == 1)
	// 	return " " + strbase;
	return r; // ADDED
}
