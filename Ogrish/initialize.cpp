#ifdef FUCKSHIT
#include "stdafx.h"

void Application :: initialize()
{
	if(GetInt("crosshair") == 1)
		Ogre::OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	
	//switch(ConfMgr :: getSingleton().GetInt("camera_mode"))
	
	cam_ctrlr -> setBulletTracer(bullet_tracer);
	// CreateTerrain();
	InitGorilla();
	CreateScene();
	init_physics();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

}
#endif