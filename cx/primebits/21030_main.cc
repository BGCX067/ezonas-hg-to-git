#include "21030.h"
#include "jokoon.h"
#include <vector>
#define n2s unbase::tumber27
#define s2n unbase::number27

int main(int n, char * arg[])
{
	// pr(unbase::number27(string("0")));
	// pr(unbase::number27(string("A")));
	// pr(unbase::number27(string("Z")));
	// pr(unbase::number27(string("A0")));
	// pr(unbase::number27(string("GG")));
	// pr(unbase::number27(string("LOL")));
	// 
	// pr(unbase::tumber27(0));
	// pr(unbase::tumber27(1));
	// pr(unbase::tumber27(26));
	// pr(unbase::tumber27(27));

	// unbase::show_mult_table27();
	// printf("0x%X\n", UINT_MAX);
	// printf("0x%lX\n", ULONG_MAX);
	// pr(unbase::int_pow(27,13)-1);
	// pr("---");

	if(n == 2)
	{
		// intg a = strtol(arg[1], NULL, 10);
		// 4645095845981
		// pr(unbase::n2s(a));
		pr(unbase::s2n(string(arg[1])));
	}

	// pr("overhead:");
	// pr(ULONG_MAX - unbase::int_pow(27, 13));

	// pr(s2n("HELLO KITTY"));
	// pr(n2s(s2n("HELLO KITTY LOL")));
	// pr(n2s(s2n("HELLO KITTY")));
	// pr();

	// unbase::dictionnary("words-nix");


	// vector<ulong> fds;
	// pr("--- BASE 27 ---");
	// FORG(9,15) {
	// 	printf("27^%02d = 0x%lu\n", i, unbase::int_pow(27, i));
	// 	printf("27^%02d = 0x%lX\n", i, unbase::int_pow(27, i)); }
	// pr("--- BASE 30 ---");
	// FORG(9,15){
	// 	printf("30^%02d = 0x%lu\n", i, unbase::int_pow(30, i));
	// 	printf("30^%02d = 0x%lX\n", i, unbase::int_pow(30, i)); }
	// pr("--- BASE 36 ---");
	// FORG(9,15){
	// 	printf("36^%02d = 0x%lu\n", i, unbase::int_pow(36, i));
	// 	printf("36^%02d = 0x%lX\n", i, unbase::int_pow(36, i));}


}