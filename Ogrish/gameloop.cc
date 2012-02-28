#include "stdafx.h"

void Application :: moveTo(ushort idx, Vec3 dest, float speed)
{
	if(idx < Nodes.size())
	{
		isMoving[idx] = true;
		Vec3 direction (Nodes[idx]->getPosition() - dest);
		velocities[idx] = direction * speed / direction.length();
	}
}
/*void Application :: check_collisions()
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
*/