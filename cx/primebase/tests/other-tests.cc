#include "jokoon.h"
#include <bitset>

intg * array;
bitset<96> * crible;
intg size_array;
intg size_sieve;

void bitset2ulong() // KOHRRRRREKT' !
{
	cout << "[B2U] partitionning bitset into an array of ulong" << endl;	
	for(intg i = 0; i < 256; ++ i)	// 0 -> 3
	// for(int i = 255; i >= 0; -- i)	// 0 -> 3
	
	// for(int i = size_array; i >= 0; -- i)	// 0 -> 3
		if((* crible)[i])
			// array[i / 64] |= (1UL << (64 - (i % 64)));
			array[3 - (i / 64)]
				|= (1UL << (i % 64));
}
// /////////////////////////////////////////////////////////////////////////
void ulong2bitset()
{
	cout << "[U2B] partitionning bitset into an array of ulong" << endl;
	for(intg i = 0; i < 256; ++ i)
	// for(int i = 255; i >= 0; -- i)
	{
		// cout << i / 64 << " " << endl;
		(* crible)[i] =
			array[3 - i / 64]
				& (1UL << (i % 64));

		// (* crible2)[i] = array[3 - (i / 64)] | (1UL << ((i % 64)));
		// cout << i / 64 << endl;
		// for(intg j = 63; j > -1; -- j)
		// (* crible2)[64 * i + j] = array[j] | (1UL << j);
		
	}
}

string number_fmt(ulong n)
{
	// cout << "(" << n << ")" << endl;
	char s[128];
	sprintf(s, "%lu", n);
	string r(s);
	reverse(r.begin(), r.end());
	int space_inserted = 0;
	size_t how_many_spaces = r.length() / 3;

	if(r.length() % 3 != 0)
		how_many_spaces += 1;

	for(int i = 1; i < how_many_spaces; ++i)
	{
		r.insert(3 * i + space_inserted, " ");
		space_inserted += 1;
	}
	reverse(r.begin(), r.end());

	return r;
}

void bitset2array() // KOHRRRRREKT' !
{
	for(intg i = 0; i < size_sieve; ++ i)	// 0 -> 3
		if((* crible)[i])
			array[size_array - (i / INTG_BITS) - 1]
				|= (1UL << (i % INTG_BITS));
	cout << "[B2A] done" << endl;
	// cout << "[B2A] some elements: " << endl;
}

void array2bitset()
{
	for(intg i = 0; i < size_sieve, i < size_array * INTG_BITS; ++ i)
		(* crible)[i] =
			array[size_array - i / INTG_BITS - 1]
				& (1UL << (i % INTG_BITS));
	cout << "[A2B] done" << endl;
}

int main()
{
	{
		// cout << strtol("100000000", 0, 5) << endl;
		// cout << strtol("10", 0, 5) << endl;
		// cout << strtol("100", 0, 30) << endl;
		// cout << strtol("10", 0, 30) << endl;
		// int n = 1;
		// FOR(10)
		// {
		// 	cout << number_fmt(n *= 11) << "." << endl;
		// }

		// cout << number_fmt(ULONG_MAX) << "." << endl;
		// cout << number_fmt(UINT_MAX) << "." << endl;
		// cout << sizeof(uint) * 8 << "." << endl;
		// cout << sizeof(ulong) * 8 << "." << endl;

		// int things [3] = {2, 4, 16};
		// things [1] |= 32;
		// cout << things [1] << endl;
		// 	int a = 43, b = 47, c = 3;
		// 	cout << a << endl;
		// 	a ^= b;
		// 	a ^= c;
		// 	cout << a << endl;
		// 	a ^= c;
		// 	a ^= b;
		// 	
		// 	cout << a << endl;
		//
	}
	crible = new bitset<96>;// (1|4|32|512);
	(*crible).reset();
	(*crible)[95] = true;
	(*crible)[80] = true;
	(*crible)[8] = true;
	(*crible)[2] = true;
	
	size_sieve = crible -> size();
	size_array = size_sieve / INTG_BITS;

	pr_("size_sieve ="); pr(size_sieve);
	pr_("size_array ="); pr(size_array);
	pr_("sizeof(intg) ="); pr(sizeof(intg));
	
	array = new intg[size_array];
	// memset(array, 0, 4*sizeof(intg));

	cout << * crible << endl;
	bitset2array();
	FOR(size_array)
		pr_(array[i]);
	prln;
	prx(array[0]);
	prx(array[1]);
	prx(array[2]);

	
	FILE * file = fopen("damnit.bit", "w");
	if(file != NULL)
	{
		pr_("wrote !"); pr(fwrite(array, INTG_BYTES, size_array, file));
		fclose(file);
		file = NULL;
	}

	delete [] array;
	delete crible;
	crible = NULL;
	array = NULL;
	//////////////////////////////////////////////////
	// backward !
	//////////////////////////////////////////////////

	array = new intg[size_array];
	crible = new bitset<96>;// (1|4|32|512);
	// memset(array, 0, 4*sizeof(ulong));

	file = fopen("damnit.bit", "r");
	if(file != NULL)
	{
		pr_("read !");
		pr(fread(array, INTG_BYTES, size_array, file));
		fclose(file);
		file = NULL;
	}

	FOR(size_array)
		pr_(array[i]);
	prln;
	prx(array[0]);
	prx(array[1]);
	prx(array[2]);

	array2bitset();
	cout << * crible << endl;

	
	delete [] array;
	delete crible;

}



// FOR(4)
// 	cout << array[i] << " ";
// cout << endl;
