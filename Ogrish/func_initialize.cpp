#include "stdafx.h"

void Application :: initialize()
{
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	cam_ctrlr -> setBulletTracer(bullet_tracer);
	lasercast-> set_hover(material_hover);
	// CreateTerrain();
	InitGorilla();

	// ########################## add entities and nodes ##########################
	//ConfMgr :: getSingletonPtr() -> AddLevel("guy");
	//ConfMgr :: getSingletonPtr() -> AddLevel("mifflin3");
	AddPlane();
	LoadEntity("bonome");
	if (configfile->getSetting("Populate") == "yes") Populate();

	AddLight("light3");
	AddLight("light3b");

	init_physics();

}