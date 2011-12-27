#include <cstdio>
#define pr(s) printf("%s\n", s)
#define prx(s) printf("0x%X\n", s)

typedef unsigned int uint;

bool get_bit(uint mask, int n)
{
	return mask & (1 << n);
}

uint get_uint_from_mask(uint n, uint top, uint bottom)
{
	// shifts right bottom times
	n >>= bottom - 1;

	// ANDs it with a top-times left-shifted FFF
	uint mask = 0xFFFFFFFF >> (top - bottom + 1);
	
	return n & mask;
}
int main()
{
	// unsigned int a = 0x7FFFFFFF;
	// unsigned int b = 0xFFFFFFFF;
	// unsigned int c = 0xFFFFFFFE;
	// // prx(a);
	// 
	// pr("with 0x7FFFFFFF");
	// printf(">> 1 = 0x%X ", a>>1); pr("least 1 is discarded");
	// printf("<< 1 = 0x%X ", a<<1); pr("most 0 is discarded");
	// pr("");	
	// 
	// pr("with 0xFFFFFFFF");
	// printf(">> 1 = 0x%X ", b>>1); pr("least 1 is discarded");
	// printf("<< 1 = 0x%X ", b<<1); pr("most 1 is discarded");
	// pr("");	
	// 
	// pr("with 0xFFFFFFFE");
	// printf(">> 1 = 0x%X ", c>>1); pr("least 0 is discarded");
	// printf("<< 1 = 0x%X ", c<<1); pr("most 1 is discarded");

	//prx(get_uint_from_mask(0x1C,5,3)); // 5 included, 3 included

	// prx(get_uint_from_mask(0x1C,5,3)); // 5 included, 3 included
	// prx(get_bit(257, 6));

	prx(~ 43542);
}