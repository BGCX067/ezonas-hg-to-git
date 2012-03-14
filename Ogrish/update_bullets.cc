#include "stdafx.h"
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
