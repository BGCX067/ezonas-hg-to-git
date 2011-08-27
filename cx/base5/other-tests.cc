#include <cstdio>
int main()
{
printf("%ld\n", 0xF800000000000000L >> 59);
printf("%ld\n", 0x03C0000000000000L >> 54);
printf("%ld\n", 0x003E000000000000L >> 49);
printf("%ld\n", 0x0001F00000000000L >> 44);
printf("%ld\n", 0x00000F8000000000L >> 39);
printf("%ld\n", 0x0000003C00000000L >> 34);
printf("%ld\n", 0x00000003E0000000L >> 29);
printf("%ld\n", 0x000000001F000000L >> 24);
printf("%ld\n", 0x0000000000F80000L >> 19);
printf("%ld\n", 0x000000000003C000L >> 14);
printf("%ld\n", 0x0000000000003E00L >>  9);
printf("%ld\n", 0x00000000000001F0L >>  4);

for(int i = 11; i >= 0; --i)
{
	printf("%016lX\n", 31L << 5*i);
}
}