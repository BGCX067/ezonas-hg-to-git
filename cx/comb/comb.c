#include <stdio.h>

typedef unsigned long ulong;
#define print(s) printf("%s\n", s)
ulong fact(ulong n)
{
	if(n < 3) return 2;
	return n * fact(n - 1);
}

ulong comb(ulong n, ulong k)
{
	// printf("5! = %ud\n", fact(5));
	// printf("32! = %ud\n", fact(32));
	ulong prod = 1;
	ulong i;
	for(i = k + 1; i <= n; ++i)
	{
		prod *= i;
		//printf("%u\n", prod);
	}
	return prod / fact(n-k);
}

int main()
{
	ulong value = 2, prev = 1;
	int i;
	for(i = 10; i < 100000; i += 10)
	{
		prev = value;
		value = comb(i, i - 5);
		if(value < prev)
		{
			print("number too big");
			break;
		}
		printf("C %u %u = \t%20lu \t %20e\n", i, i - 5, value, (double)value);
	}	
}
