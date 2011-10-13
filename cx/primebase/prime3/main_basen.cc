#include "basex.h"
#include "jokoon.h"

int main(int n, char * arg[])
{
	if(n == 3)
	{
		intg n = strtol(arg[1], NULL, 10);
		unsigned int base = strtol(arg[2], NULL, 10);
		p("using ") << n << " and " << base << " as arguments" << endl;
		number num = basex :: z(n, base);
		FOR_ITR(unsigned int, num)
		{
			cout << (* itr) << ", ";
		}
		cout << "end" << endl;
	}
	else
	{
		pr("at least 2 arguments, number and base");
	}
}