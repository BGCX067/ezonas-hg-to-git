#include "basex.h"
#include "jokoon.h"
#include <vector>

int main(int n, char * arg[])
{
	if(n == 2)
		pr(basex::s2n36(string(arg[1])));
	if(n == 3)
		pr(basex::n2s36(strtol(arg[2], NULL, 10)));
}