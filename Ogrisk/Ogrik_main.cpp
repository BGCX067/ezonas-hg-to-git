#include "stdafx.h"

#ifdef __APPLE__
int main()
#elif _CONSOLE
int _main(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#else
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	Application :: Instantiate();
	Application :: GetSingleton() -> go();
	return 0;
}

