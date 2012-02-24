#include "stdafx.h"

void Application :: initialize()
{
	{ // ----- various options -----
		if(GetInt("crosshair") == 1)
			OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
		//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

		scmgr->getRootSceneNode()->createChildSceneNode()
			->attachObject(scmgr->createEntity("mifflin3.mesh"));
		cam_ctrlr -> setBulletTracer(bullet_tracer);
		InitGorilla();
	}
	{ // ----- scene creation -----
		// AddLevel("guy");
		// AddLevel("mifflin3");

		AddPlane();
		lasercast->last_entity = entplane;
		LoadEntity("bonome");
		material_hover = create_hover_material
			(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
		if (configfile->getSetting("Populate") == "yes")
			Populate();

		AddLight("light3");
		AddLight("light3b");
	}
	
	{// ----- physics ----- (todo)
		sphere_radius_squared = GetFloat("sphere_radius");
		sphere_radius_squared *= sphere_radius_squared;
		sphere = new btSphereShape(GetFloat("sphere_radius"));

		Vec3 temp;
		for(auto it = Nodes.begin(); it != Nodes.end(); ++ it)
		{
			btCollisionObject * colobj = new btCollisionObject;
			colobj->setCollisionShape(sphere);
			temp = (*it)->getPosition();
			colobj->getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
			collisionWorld->addCollisionObject(colobj);
			colobj->setUserPointer(*it);
		}
	}
}