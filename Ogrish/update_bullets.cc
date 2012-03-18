#include "stdafx.h"

void Application :: Fire()
{
	// reinitialize bullet position and orientation
	n_bullet[nextbullet] -> setPosition
		(camera -> getDerivedPosition() + Vec3(0, offset_x, offset_y));
	n_bullet[nextbullet] -> setOrientation(camera -> getDerivedOrientation());
	++nextbullet; nextbullet %= BULLET_MAX;
}
void Application :: update_bullets()
{
	FOR(BULLET_MAX)
		n_bullet[i] -> translate(0, 0, -timeSinceLastFrame * bullet_speed, Node::TS_LOCAL);
	if(trigger_pulled)
	{
		time_stack += timeSinceLastFrame;

		if (time_stack > fire_delay)
		{ 
			Fire();	
			recoil_event();
		}
	}
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
void Application :: trigger_pull()
{
	if(!next_bullet_ready) Fire();
	trigger_pulled = true;
}
void Application :: trigger_release()
{
	trigger_pulled = false;
	auto_shots_fired = 0;
}
