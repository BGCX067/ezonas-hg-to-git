#include "stdafx.h"

void Application :: initialize()
{
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	cam_ctrlr -> setBulletTracer(bullet_tracer);
	// CreateTerrain();
	InitGorilla();

	// scene creation
	// AddLevel("guy");
	// AddLevel("mifflin3");
	AddPlane();
	last_entity_raycast = entplane; // for current target
	current_ent_raycast = entplane;

	LoadEntity("bonome");
	material_hover = create_hover_material(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
	if (configfile->getSetting("Populate") == "yes") Populate();

	AddLight("light3");
	AddLight("light3b");

	init_physics();

}