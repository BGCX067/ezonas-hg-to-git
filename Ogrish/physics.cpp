#include "stdafx.h"

#ifdef PHYSICS
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
}
#endif

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

/*
    btBroadphaseInterface				* broadphase;
    btDefaultCollisionConfiguration		* collisionConfiguration;
    btCollisionDispatcher				* dispatcher;
	btCollisionWorld					* collisionWorld;

	btCollisionWorld :: ContactResultCallback * result;
	btTransform transf;
	btSphereShape * sphere;
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;

*/
/*
	int numManifolds = world->getDispatcher()->getNumManifolds();
	for (int i=0;i<numManifolds;i++)
	{
		btPersistentManifold* contactManifold =  world->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = static_cast<btCollisionObject*>(contactManifold->getBody0());
		btCollisionObject* obB = static_cast<btCollisionObject*>(contactManifold->getBody1());
	
		int numContacts = contactManifold->getNumContacts();
		for (int j=0;j<numContacts;j++)
		{
			btManifoldPoint& pt = contactManifold->getContactPoint(j);
			if (pt.getDistance()<0.f)
			{
				const btVector3& ptA = pt.getPositionWorldOnA();
				const btVector3& ptB = pt.getPositionWorldOnB();
				const btVector3& normalOnB = pt.m_normalWorldOnB;
			}
		}
	}


*/

