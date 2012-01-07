#include "stdafx.h"

#ifdef __APPLE__
int main()
#elif _CONSOLE
int main(int argc, char * argv[])
#else
int WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	Application :: Instantiate();
	Application :: getSingletonPtr() -> go();
	return 0;
}

