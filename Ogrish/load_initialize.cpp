#include "stdafx.h"

void Application :: initialize()
{
// ----- various options -----
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	cam_ctrlr -> setBulletTracer(bullet_tracer);
	InitGorilla();
	
// ----- scene creation -----
	scmgr->getRootSceneNode()->createChildSceneNode()
		->attachObject(scmgr->createEntity("mifflin3.mesh"));

	AddPlane();
	lasercast->last_entity = entplane;
	LoadEntity("bonome");
	material_hover = create_hover_material
		(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
	if (configfile->getSetting("Populate") == "yes")
		Populate();

	AddLight("light3");
	AddLight("light3b");
	
	
// ----- physics ----- (todo)
	sphere_radius_squared = GetFloat("sphere_radius");
	sphere_radius_squared *= sphere_radius_squared;
	sphere = new btSphereShape(GetFloat("sphere_radius"));

	Vec3 temp;
	//for(auto it = Nodes.begin(); it != Nodes.end(); ++ it)
	Nodes.push_back(scmgr->getSceneNode("target"));

	size_t sz = Nodes.size();
	for(size_t i = 0; i < sz; ++ i)
		add_col_obj(i);
	
}
void Application :: add_col_obj(size_t index)
{
	assert(index >= Nodes.size());

	btCollisionObject * colobj = new btCollisionObject;
	colobj->setCollisionShape(sphere);
	temp = Nodes[index]->getPosition();
	colobj->getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
	collisionWorld->addCollisionObject(colobj);
	colobj->setUserPointer(Nodes[index]);
	
}