#include "jokoon.h"

int main()
{
	FORG(20, 256)
	{
		if(i % 16 == 0) prln;
		printf("%c ", (unsigned char)i);
	}
	prln;
}