#include "stdafx.h"
void Application :: init_bullet()
{
	sphere_radius_squared = GetFloat("sphere_radius");
	sphere_radius_squared *= sphere_radius_squared;
	sphere = new btSphereShape(GetFloat("sphere_radius"));

	Vec3 temp;
	//assert(Nodes.empty());
	Nodes.push_back(scmgr->getSceneNode("target"));
	size_t sz = Nodes.size();
	for(size_t i = 0; i < sz; ++ i)
	{
		add_col_obj(i);
		//PRINTLOG(Nodes[i]->getName());
	}
}
void Application :: loop_bullet()
{
	// mirror Node position with collision objects
	size_t sz = Nodes.size();
	assert(collisionWorld->getCollisionObjectArray().size() == Nodes.size());
	for(size_t i = 0; i < sz; ++ i)
	{
//		temp = Nodes[i]->getPosition();
		temp = Nodes[i]->_getDerivedPosition();
		collisionWorld->getCollisionObjectArray()[i]->
			getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
		Nodes[i]->showBoundingBox(false);
	}

	// check collisions with bullet (yay)
	collisionWorld->performDiscreteCollisionDetection();
	size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		//PRINTLOG("collision detected ! "+TO_STR(i));
		btPersistentManifold* contactManifold = 
			collisionWorld->getDispatcher() -> getManifoldByIndexInternal(i);

		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>(contactManifold -> getBody0())
				-> getUserPointer()) -> showBoundingBox(true);

		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>(contactManifold -> getBody1())
				-> getUserPointer()) -> showBoundingBox(true);
	}
}
void Application :: add_col_obj(size_t index)
{
	assert(index < Nodes.size());

	btCollisionObject * colobj = new btCollisionObject;
	colobj->setCollisionShape(sphere);
//	temp = Nodes[index] -> getPosition();
	temp = Nodes[index] -> _getDerivedPosition();
	colobj -> getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
	colobj -> setUserPointer(Nodes[index]);
	collisionWorld -> addCollisionObject(colobj);
	hasCollided.push_back(false);
}

