#include "21030.h"

int main()
{
	unbase u;
	u.show30(0x5f3759df);
	u.show36(0x5f3759df);
	cout << '-' << endl;
	u.show30(0x5f3759df);
	cout << '-' << endl;
	u.show30("100");
	u.show30("1000");
	u.show30("10000");
	u.show30("100000");
	u.show30("1000000");

}
