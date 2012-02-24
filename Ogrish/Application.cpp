#include "stdafx.h"

template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

void Application :: go ()
{
	root -> startRendering();
	//while(!stop) root ->renderOneFrame();
}


