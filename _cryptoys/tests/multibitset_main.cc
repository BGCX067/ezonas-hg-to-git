#include "multibitset.h"

int main()
{
	multibitset m(0x3000000);
	// m[100] = false;
	m.write(200, true);
	cout << m.read(300) << endl;
	
	m.flip();
}