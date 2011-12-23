#include "basex.h"
#include <gmpxx.h>
number basex :: z(intg n, unsigned int base)
{
	number r;
	int exponent = 10;
	// pr("hello to universal base conversion");
	while (n > int_pow (base, exponent))
	{
		-- exponent;
		p(exponent)<<" ";
	}
	p("exponent = ") << exponent << endl;
	intg rest = n;
	while (exponent >= 0) // loop
	{
		if (n >= int_pow ((intg)base, exponent))
		{
			r.push_back(rest / int_pow(base, exponent));
			rest %= int_pow(base, exponent);
		}
		-- exponent;
	}
	return r;
}
number basex :: z(mpz_class n, unsigned int base)
{
	number r;
	int exponent = 1;
	// while (n > int_pow (base, exponent))
	mpz_class t;

	mpz_ui_pow_ui(t.get_mpz_t(), base, exponent); // t = n ^ exponent
	pr(t);
	pr(n);
	// pr(cmp(t, n))
	pr((n >= t));
	while (n > t)
	{
		++ exponent;
		mpz_ui_pow_ui(t.get_mpz_t(), base, exponent); // t = n ^ exponent
		// p(t) << " ";
		// p(exponent)<<" ";
	}
	p("exponent = ") << exponent << endl;
	// intg rest = n;
	mpz_class rest(n);
	while (exponent >= 0) // loop
	{
		mpz_ui_pow_ui(t.get_mpz_t(), base, exponent);
		// if (n >= int_pow ((intg)base, exponent))
		// cout << rest << " " << t << endl;
		if (cmp(n, t) != -1)
		{
			// unsigned int f = rest / int_pow(base, exponent);
			mpz_class d;
			mpz_ui_pow_ui(d.get_mpz_t(), base, exponent);
			r.push_back((mpz_class(rest / d)).get_ui());
			// rest %= int_pow(base, exponent);
			rest %= d;
		}
		-- exponent;
	}
	return r;
}
