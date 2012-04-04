// cryptest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdio>
#include <cstdlib>

#define MAX_COMB 1024

int values[MAX_COMB];

int f(int k, int steps)
{
	if(k > 1 && steps > 0 && k < MAX_COMB)
	{
		int a = f(values[k], steps + 1);
		return a; // comb(2, k)
	}
	return -1;
}

void fu(int startvalue, int steps)
{
	for(int i = 0; i < steps && startvalue < MAX_COMB; ++ i)
	{
		startvalue += values[startvalue];
		printf("step %d: %d\n",i, startvalue);
	}
}
void show_values(int startvalue, int steps)
{
	printf ("showing values for startvalue %d\n", startvalue);
	for(int i = 2; i <= steps; ++i)
		printf("%d\n", f(startvalue,i));
}

int _tmain(int argc, _TCHAR* argv[])
{
	for(int i = 0; i < MAX_COMB; ++i)
		values[i] = (i*(i-1))/2;


	fu(2, 10);

	system("PAUSE");
	return 0;
}

