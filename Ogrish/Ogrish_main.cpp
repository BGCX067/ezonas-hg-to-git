#include "stdafx.h"

#ifdef __APPLE__
int main()
#else
int main(int argc, char * argv[])
#endif
{
	//Application :: Instantiate();
	Application :: sglt() -> go();
	return 0;
}

