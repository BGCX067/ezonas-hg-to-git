#include "primewords.h"

int main()
{
	workode * w = new workode();
// 	w -> gen(1000000000000);
	w -> read ("crible");
	w -> show();

	delete w;
}