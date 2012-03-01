#include "stdafx.h"

void Application :: initialize()
{
// ----- various options -----
	window -> reposition(20, 20);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	cam_ctrlr -> setBulletTracer(bullet_tracer);
	PRINTLOG("------- initializing GUI -------");
	InitGorilla();
	
// ----- scene creation -----
	PRINTLOG("------- creating the scene -------");
	if(GetString("loadlevel") == "yes")
	scmgr->getRootSceneNode()->createChildSceneNode()
		->attachObject(scmgr->createEntity(GetString("level")));

	AddPlane();
	lasercast->last_entity = entplane;
	LoadEntity("bonome");
	cam_ctrlr->setCameraMode(3);
	material_hover = create_hover_material
		(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
	if (configfile->getSetting("Populate") == "yes")
		Populate();

	AddLight("light3");
	AddLight("light3b");

	PRINTLOG("------- creating physics -------");
	init_bullet();
	
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("        FINISHED INITIALIZING OGRE3D; begginning gameloop        ");
	PRINTLOG("-----------------------------------------------------------------");
}
