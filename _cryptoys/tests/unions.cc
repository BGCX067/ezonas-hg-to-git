#include "jokoon.h"

struct thing
{
	int v;
};

int main()
{
	// thing t;
	union
	{
		float f;
		int i;	
		thing t;
	};
	f = 2.0;
	// i = 2;
	pr(f);
	pr(i);
	prx2(i);

}