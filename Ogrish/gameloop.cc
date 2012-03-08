#include "stdafx.h"
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat"
	);
	timeSinceLastFrame = evt.timeSinceLastFrame;
	size_t sz = velocities.size();
/*	for(size_t i = 0; i < sz; ++ i)
		Nodes[i]->translate(velocities[i] * timeSinceLastFrame);*/
	keyboard -> capture();
	mouse -> capture();

	n_master -> translate
	(n_yawpitch_ptr -> getOrientation() * translate * moving_speed * timeSinceLastFrame);
	assert(translate.length() <= 1.0f);
	update_physics();
	update_bullets();
#ifdef LASERCAST
	lasercast->update();
#endif
	return ! stop;
}
void Application :: update_physics()
{
	// mirror Node position with collision objects
	size_t sz = Nodes.size();
	assert(colw->getCollisionObjectArray().size() == Nodes.size());
	for(size_t i = 0; i < sz; ++ i)
	{
		// temp = Nodes[i]->getPosition();
		temp = Nodes[i]->_getDerivedPosition();
		colw->getCollisionObjectArray()[i]->
			getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
		Nodes[i]->showBoundingBox(false);
	}
	
	// setting ray to camera orientation
	temp = camera -> getRealPosition();// + camera ->getRealDirection()*10.0f;
	temp1 = (camera ->getRealDirection() - temp);//*10000.0f;

	raycallback.m_rayFromWorld = btVector3(temp.x,temp.x,temp.x);
	raycallback.m_rayToWorld = btVector3(temp1.x,temp1.y,temp1.z);
	colw -> rayTest
		(raycallback.m_rayFromWorld, raycallback.m_rayToWorld, raycallback);
	if(raycallback.hasHit())
	{
		bttemp = raycallback.m_hitPointWorld;
		n_laserdot -> setPosition(Vec3(bttemp.x(),bttemp.y(),bttemp.z()));
	}
	colw->performDiscreteCollisionDetection();
	

	// perform collision detection and retrieve collision results
	//update_laser(Vec3(bttemp.x(),bttemp.y(),bttemp.z()));

	size_t num = dispatcher->getNumManifolds();
	for(size_t i = 0; i < num; ++i)
	{
		//PRINTLOG("collision detected ! "+TO_STR(i));
		btPersistentManifold* contactManifold = 
			colw -> getDispatcher() -> getManifoldByIndexInternal(i);

		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>
				(contactManifold -> getBody0())
					-> getUserPointer())
						-> showBoundingBox(true);
		static_cast<SceneNode*>
			(static_cast<btCollisionObject*>
				(contactManifold -> getBody1())
					-> getUserPointer())
						-> showBoundingBox(true);

	}
}
void Application :: update_laser()
{
	//bb_beam -> updateChainElement
	//	(0, 0, BillboardChain :: Element
	//		(result, laser_width, 0, ColourValue()));
	//bb_beam -> updateChainElement
	//	(0, 1, BillboardChain :: Element
	//	(camera -> getRealPosition() + Vec3(0,2,0), laser_width, 0, ColourValue()));

	// last_entity, current_entity;
	//if (ent_check == last_entity);
	//else
	//{
	//	//static_cast<SceneNode*>(last_entity->getParentNode())->showBoundingBox(false);
	//	//static_cast<SceneNode*>(ent_check->getParentNode())->showBoundingBox(true);
	//	//last_entity = ent_check;
	//}
}
void Application :: update_bullets()
{
	FOR(BULLET_MAX)
		n_bullet[i] -> translate(0, 0, -  timeSinceLastFrame * bullet_speed, Ogre :: Node :: TS_LOCAL);
	time_stack += timeSinceLastFrame;
	if (time_stack > fire_delay)
	{
		time_stack = 0.0f;
		was_fired = false;
	}
	if(trigger_state && !was_fired)
		Fire();
	
	// bullet raycast
	/* todo
	ray_start = camera ->getDerivedPosition();
	ray_end = ray_start + camera ->getDerivedDirection();

	arg_start = btVector3(ray_start.x, ray_start.y, ray_start.z);
	arg_end = btVector3(ray_end.x, ray_end.y, ray_end.z);
	// btCollisionWorld :: ClosestRayResultCallback RayCallback(arg_start, arg_end);
	// Perform raycast
 
	if(callbacks[nextbullet].hasHit())
	{
		//End = RayCallback.m_hitPointWorld;
		//Normal = RayCallback.m_hitNormalWorld;
		// Do some clever stuff here
	}
	collisionWorld->rayTest(arg_start, arg_end, callbacks[nextbullet]);
	*/

	//if(was_fired == true)
	//{
}
void Application :: Fire()
{
	if (!was_fired)
	{
		n_bullet[nextbullet] -> setPosition
			(camera -> getDerivedPosition() + Vec3(0, offset_x, offset_y));
		n_bullet[nextbullet] -> setOrientation(camera -> getDerivedOrientation());
		++nextbullet;
		nextbullet %= BULLET_MAX;
		was_fired = true;
	}
}
void Application :: FirePull() {} void Application :: FireRelease() {}
void Application :: diagnose()
{
	//PRINTLOG(str_vect(n_laserdot->getPosition()));
	PRINTLOG(str_vect(camera->getRealDirection()));
	//PRINTLOG(str_vect(camera->getRealDirection()));
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
bool Application :: frameEnded(const FrameEvent & evt) { return true; }
bool Application :: frameStarted(const FrameEvent & evt) { return true; }
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
