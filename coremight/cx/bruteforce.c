#include <stdio.h>
#define FIRST 'a'
#define LAST 'z'
//[]|}[]|}
void roll(char * t, int i);
void rollup(char * t, int i);

void roll(char * t, int i)
{
	if( t[i] == LAST) rollup(t, i);
	else t [i]++;
}

void rollup(char * t, int i)
{
	t[i] = FIRST;
	roll(t, i+1);
}

int main()
{
	char t[10] = "aaaaaaaaa";
	for(int i = 0;;)
	{
		printf("%s\t",t);
		roll(t, i);
		//getchar();
	}
}
