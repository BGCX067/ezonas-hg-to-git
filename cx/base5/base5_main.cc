#include "base5.h"

int main(int n, char * arg[])
{
	if(n == 1)
	{
		// print("please supply arguments");
		base5 b;
		// string str("DESTRLCTIBLE");
		//ring str("123456789ABC");
		string str("ZZZZZZZZZZZZ");
//		cout << b.encode(str) << endl;
		cout << b.decode(b.encode(str)) << endl;

	}
	if(n == 2)
	{
		string s(arg[1]);		
	}
	
}