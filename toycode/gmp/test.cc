#include <gmpxx.h>
#include "jokoon.h"

int main()
{
	mpz_class n, p, q;
	n.set_str("2", 10);
	p.set_str("5", 10);
	// q.set_str("5", 10);
	cout << n << endl;
	cout << "cmp(2, 5)" << " = " << (n < p) << endl;
	cout << "cmp(5, 2)" << " = " << (n > p) << endl;
	// cout << "cmp(2, 5)" << " = " << cmp(n, p) << endl;
	// cout << "cmp(5, 2)" << " = " << cmp(p, n) << endl;
	// cout << "cmp(n, n)" << " " << cmp(n, n) << endl;
	
	mpz_t c;
	mpz_init(c);
	mpz_class b(c);
	
	mpz_pow_ui(q.get_mpz_t(), n.get_mpz_t(), 5);
	q /= 4;
	pr(q);
}