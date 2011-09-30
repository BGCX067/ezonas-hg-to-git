#include "basex.h"
#include "jokoon.h"
#include <vector>

int main(int n, char * arg[])
{
	// pr(basex::number27(string("0")));
	// pr(basex::number27(string("A")));
	// pr(basex::number27(string("Z")));
	// pr(basex::number27(string("A0")));
	// pr(basex::number27(string("GG")));
	// pr(basex::number27(string("LOL")));
	// 
	// pr(basex::tumber27(0));
	// pr(basex::tumber27(1));
	// pr(basex::tumber27(26));
	// pr(basex::tumber27(27));

	// basex::show_mult_table27();
	// printf("0x%X\n", UINT_MAX);
	// printf("0x%lX\n", ULONG_MAX);
	// pr(basex::int_pow(27,13)-1);
	// pr("---");

	if(n == 2)
	{
		// intg a = strtol(arg[1], NULL, 10);
		// 4645095845981
		// pr(basex::n2s(a));
		pr(basex::s2n(string(arg[1])));
	}

	// pr("overhead:");
	// pr(ULONG_MAX - basex::int_pow(27, 13));

	// pr(s2n("HELLO KITTY"));
	// pr(n2s(s2n("HELLO KITTY LOL")));
	// pr(n2s(s2n("HELLO KITTY")));
	// pr();

	// basex::dictionnary("words-nix");


	// vector<ulong> fds;
	// pr("--- BASE 27 ---");
	// FORG(9,15) {
	// 	printf("27^%02d = 0x%lu\n", i, basex::int_pow(27, i));
	// 	printf("27^%02d = 0x%lX\n", i, basex::int_pow(27, i)); }
	// pr("--- BASE 30 ---");
	// FORG(9,15){
	// 	printf("30^%02d = 0x%lu\n", i, basex::int_pow(30, i));
	// 	printf("30^%02d = 0x%lX\n", i, basex::int_pow(30, i)); }
	// pr("--- BASE 36 ---");
	// FORG(9,15){
	// 	printf("36^%02d = 0x%lu\n", i, basex::int_pow(36, i));
	// 	printf("36^%02d = 0x%lX\n", i, basex::int_pow(36, i));}


}