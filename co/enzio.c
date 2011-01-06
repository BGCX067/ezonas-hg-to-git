#include <stdio.h>


enum enzio
{
	n_0,
	n_1,
	n_2,
	n_3,
	n_4,
	n_5,
	n_6,
	n_7,
	n_8,
	n_9,


	a_A,
	a_B,
	a_C,
	a_D,
	a_E,
	a_F,
	a_G,
	a_H,
	a_I,
	a_J,
	a_K,
	a_L,
	a_M,
	a_N,
	a_O,
	a_P,
	a_Q,
	a_R,
	a_S,
	a_T,
	a_U,
	a_V,
	a_W,
	a_X,
	a_Y,
	a_Z,




	c_sp,

	c_dot,
	c_comma,
	c_colon,
	c_semicolon,
	c_exclam,
	c_inter,

	c_hash,
	c_amper,
	c_at,
	c_dollar,
	c_percent,
	c_caret,
	c_star,
	c_bar,
	c_tilde,

	c_minus,
	c_plus,
	c_equal,
	c_multi,
	c_divide,

	c_slash,
	c_backslash,

	c_quote,
	c_doublequote,

	c_less,
	c_greater,

	c_braceopen,
	c_braceclose,

	c_bracketopen,
	c_bracketclose,

	c_bracecurlopen,
	c_bracecurlclose,

	c_end
	};
/*
	c_,
	c_,
	c_,
	c_,
	c_,
	c_,
	c_,
	c_,
	c_,
	c_,


}
*/

char decode(int n)
{
	if (n >= a_A || n <= a_Z) return n + '@' - a_A;
	else if (n >= n_0 || n <= n_9) return n + '0';
	else if (n >= n_0 || n <= c_end)
	switch(n)
	{
		case c_sp: return ' ';
		case c_dot: return '.';
		case c_comma: return ',';
		case c_colon: return ':';
		case c_semicolon: return ';';

		case c_exclam: return '!';
		case c_inter: return '?';

		case c_hash: return '#';
		case c_amper: return '&';
		case c_at: return '@';
		case c_dollar: return '$';
		case c_percent: return '%';
		case c_caret: return '^';
		case c_star: return '*';
		case c_bar: return '|';
		case c_tilde: return '~';

		case c_minus: return '-';
		case c_plus: return '+';
		case c_equal: return '=';
//		case c_multi: return '¬';
//		case c_divide: return '÷';

		case c_slash: return '/';
		case c_backslash: return '\\';

		case c_quote: return '\'';
		case c_doublequote: return '"';

		case c_less: return '<';
		case c_greater: return '>';

		case c_braceopen: return '(';
		case c_braceclose: return ')';

		case c_bracketopen: return '[';
		case c_bracketclose: return ']';

		case c_bracecurlopen: return '{';
		case c_bracecurlclose: return '}';

	}

}

int encode(char c)
{}
void testd(int n) { printf("%d: %c\n", n, decode(n)); }
int main()
{

	printf ("%d\n", c_end + 1);
	testd(a_E);
	testd(c_exclam);
	//return 1;
}

