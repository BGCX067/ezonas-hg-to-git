#include "stdafx.h"

#ifdef __APPLE__
int main()
#elif _CONSOLE
int main(int argc, char * argv[])
#else
int /*__stdcall*/ WinMain(HINSTANCE a, HINSTANCE b, LPSTR c, int d)
#endif
{
	Application app;
	app.init();
	LOGMSG("------------- init started -------------");
	app.init_resources();
	app.init_inputs();
	app.init_scene();
	app.init_other();
	LOGMSG("------------- init ended -------------");
	app.root->startRendering();
	return 0;
}
