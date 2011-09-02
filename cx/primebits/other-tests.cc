#include "jokoon.h"
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

int main()
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
	cout << number_fmt(ULONG_MAX) << "." << endl;
	cout << number_fmt(UINT_MAX) << "." << endl;
	
}