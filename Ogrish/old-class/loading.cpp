#include "stdafx.h"

void Application :: init_physics()
{
	btCollisionObject * colobj = new btCollisionObject;
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
