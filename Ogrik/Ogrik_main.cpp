#include "stdafx.h"

#ifdef __APPLE__
int main()
#else
int WINAPI WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	Application app;
	app.startup();
	
	while(app.keepRunning())
	{
		app.renderOneFrame();
	}

	return 0;
}

