#include <iostream>
using namespace std;

int main(int n, char * arg[])
{
	if(n == 1)
	{
		cout << "please supply argument" << endl;
	}
	if(n == 2)
	{
		unsigned long long m = strtol(arg[1], 0, 16);
		cout << "decimal number is " << m << endl;
		if (m != 0)
		{
			unsigned long long size[5] = {0, 0, 0, 0, 0};
			size[0] = m / 0x400; //1024
			size[1] = m / 0x100000; // 1024 ^ 2
			size[2] = m / 0x40000000; // 1024 ^ 3
			size[3] = m / 0x10000000000; // 1024 ^ 4
			size[4] = m / 0x4000000000000; // 1024 ^ 5
			cout << "results:" << endl;
			cout << size[0] << " KB" << endl;
			cout << size[1] << " MB" << endl;
			cout << size[2] << " GB" << endl;
			cout << size[3] << " TB" << endl;
			cout << size[4] << " PB" << endl;

		}
		
	}
}