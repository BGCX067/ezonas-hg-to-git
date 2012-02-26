#include "stdafx.h"

void Application :: handle_bullet()
{
	size_t sz = Nodes.size();
	for(size_t i = 0; i < sz; ++ i)
	{
	// mirror Node position with collision objects
		temp = Nodes[i]->getPosition();
		collisionWorld->getCollisionObjectArray()[i]->
			getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
		Nodes[i]->showBoundingBox(false);
	}
	collisionWorld->performDiscreteCollisionDetection();

	// check collisions with bullet (yay)
	size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		PRINTLOG("detection detected ! "+TO_STR(i));
		btPersistentManifold* contactManifold = 
			collisionWorld->getDispatcher() -> getManifoldByIndexInternal(i);
		// I'm starting to hate type systems
		static_cast<SceneNode*>(static_cast<btCollisionObject*>
			(contactManifold -> getBody0()) -> getUserPointer()) -> showBoundingBox(true);
		static_cast<SceneNode*>(static_cast<btCollisionObject*>
			(contactManifold -> getBody1()) -> getUserPointer()) -> showBoundingBox(true);
	}
}
void Application :: moveTo(ushort idx, Vec3 dest, float speed)
{
	if(idx < Nodes.size())
	{
		isMoving[idx] = true;
		Vec3 direction (Nodes[idx]->getPosition() - dest);
		velocities[idx] = direction * speed / direction.length();
	}
}
void Application :: check_collisions()
{
// brute force distance check
	size_t num = Nodes.size();
	for(size_t i = 0; i < num; ++i)
		for(size_t j = i + 1; j < num; ++j)
		{
			float fd = Nodes[i]->getPosition().squaredDistance(Nodes[j]->getPosition());
			if(Nodes[i]->getPosition().squaredDistance(Nodes[j]->getPosition()) < sphere_radius_squared)
			{
				Nodes[i]->showBoundingBox(true);
				Nodes[j]->showBoundingBox(true);
			}
			else
			{
				Nodes[i]->showBoundingBox(false);
				Nodes[j]->showBoundingBox(false);
			}
		}
}
