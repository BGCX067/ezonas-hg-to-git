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
			setWorldTransform(btTransform(btQuaternion(), btVector3(temp.x, temp.y, temp.z)));
	}
	
	size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		
	}

}
#endif

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

