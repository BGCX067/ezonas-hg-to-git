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
	lasercast->last_entity = entplane;
	LoadEntity("bonome");
	material_hover = create_hover_material(scmgr->getEntity("bonome")
		->getSubEntity(0)->getMaterial());
	if (configfile->getSetting("Populate") == "yes")
		Populate();

	AddLight("light3");
	AddLight("light3b");

	// physics: todo

	sphere_radius_squared = GetFloat("sphere_radius");
	sphere_radius_squared *= sphere_radius_squared;
	sphere = new btSphereShape(GetFloat("sphere_radius"));

	for(auto it = Nodes.begin(); it != Nodes.end(); ++ it)
	{
		btCollisionObject * colobj = new btCollisionObject;
		colobj->setCollisionShape(sphere);
		temp = (*it)->getPosition();
		colobj->getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
		collisionWorld->addCollisionObject(colobj);
	}
}