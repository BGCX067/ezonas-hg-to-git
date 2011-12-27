#include "jokoon.h"
#include <bitset>

int main()
{
	// bitset<64> b(16UL);
	// cout << b << endl;
	// cout << b.to_ulong() << endl;
	FILE * file = fopen("damnit.bit", "w");
//	int ar [1] = {64}, t [1] = {0};

	fwrite(ar, 4, 1, file);
	
	fclose(file);

	file = fopen("damnit.bit", "r");
//	fread(t, 4, 1, file);

	// cout << ar[0] << endl;
//	cout << t[0] << endl;

	fclose(file);

}