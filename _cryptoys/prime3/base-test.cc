#include "basex.h"
// #include "jokoom"
int main()
{
	pr("--- 30 ---");
	pr(basex :: n2s30(29));
	pr(basex :: n2s30(30));
	pr(basex :: n2s30(31));
	pr(basex :: n2s30(899));
	pr(basex :: n2s30(900));

	pr(basex :: s2n30("0"));
	pr(basex :: s2n30("a"));
	pr(basex :: s2n30("B"));
	pr(basex :: s2n30("T"));
	pr(basex :: s2n30("a0"));
	// pr(basex :: num30('0'));
	// pr(basex :: num30('1'));
	// pr(basex :: num30('9'));
	// pr(basex :: num30('a'));
	// pr(basex :: num30('t'));

	// pr("--");
	// pr(basex :: chr30(0));
	// pr(basex :: chr30(1));
	// pr(basex :: chr30(2));
	// pr(basex :: chr30(29));
	// pr(basex :: chr30(30));

	pr("--- 36 ---");
	// pr(basex :: num36('0'));
	// pr(basex :: num36('1'));
	// pr(basex :: num36('9'));
	// pr(basex :: num36('a'));
	// pr(basex :: num36('t'));
	// pr(basex :: num36('z'));
	// 
	// pr("--");
	// pr(basex :: chr36(0));
	// pr(basex :: chr36(1));
	// pr(basex :: chr36(2));
	// pr(basex :: chr36(35));
	// pr(basex :: chr36(36));

}