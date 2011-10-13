#include "jokoon.h"

string num_fmt(intg n)
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
	pr(num_fmt(ULONG_MAX));
	printf("%.24e\n", float(ULONG_MAX));
}