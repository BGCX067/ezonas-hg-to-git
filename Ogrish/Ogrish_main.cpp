#include "stdafx.h"
Application * appli = NULL;

#ifdef __APPLE__
int main()
#elif _CONSOLE
int main(int argc, char * argv[])
#else
int WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	appli = new Application;
	appli -> init();
	appli -> go();
	return 0;
}

