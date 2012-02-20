#include "stdafx.h"

void Application :: handle_bullet()
{
	//for(auto it = Nodes.begin(); it != Nodes.end(); ++ it)
	size_t sz = Nodes.size();
	// mirroring movements
	for(size_t i = 0; i < sz; ++ i)
	{
		temp = Nodes[i]->getPosition();
		btCollisionObject * colobj;
		collisionWorld->getCollisionObjectArray()[i]->
			getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
	}
	
	size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		// mirror Node position with collision objects
	}

	//collisionWorld->
}

void Application :: moveTo(int idx, Vec3 dest, float speed)
{
	if(idx < Nodes.size())
	{
		isMoving[idx] = true;
		Vec3 direction (Nodes[idx]->getPosition() - dest);
		velocities[idx] = direction * speed / direction.length();
	}
}

// brute force distance check
void Application :: check_collisions()
{
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
