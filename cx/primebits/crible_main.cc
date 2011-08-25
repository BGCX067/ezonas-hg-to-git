#include "primecrible.h"
#include "stdio.h"

int main(int n, char * arg[])
{
	// uint in = 120, l = 80;
	// if (n >= 2) in = strtol(arg[1], NULL, 0);
	// if (n >= 3)  l = strtol(arg[2], NULL, 0);

	if(n == 1)
	{
		cout << "no args given, will use default settings" << endl;
		Crible c(BITS);//, l);
		c.Generate();
		//c.Pack();
		//c.ShowPrimes();
	}
	if(n == 2)// and arg[1] < ('9' + 1) and arg[1] > ('0' - 1))
	{
		int value = atoi(arg[1]);
		cout << "Caught " << value << " as maximum" << endl;

 		Crible c(value);
		c.Generate();
		c.Pack();
		c.WriteFile();
	}
	
	//c.ShowPrimeByPosition(10001);
	//c.ShowArray();
	// c.ShowPrimes36();
//	system("pause");
    //cin.get();
	// return 0xdeadbeef;
	
	// c.ShowPrimes();
	return 347;

}
/*
void number_format(long n)
{
	// int r = n;
	// do
	// {
	// 	r /= 1000;
	// }
	// while(r < 1)
	char s[256], r[256];
	itoa(n, s, 10);
	int size = strlen(s);
	int cursor = size - 1;
	// copy s to r in reverse order
	for (int i = 0, i < size; ++ i)
	{
		r[size - i] = s[i];
	}
	r[size + 1] = '\0';
	int cursor = 0;
	while (cursor < size)
	{
		
	}
}



*/



