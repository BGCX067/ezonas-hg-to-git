#include "stdafx.h"

#define N_BUFFERS 32
void Application :: calculate_recoil()
{
	if(trigger_pulled && time_buffer[current_recoil] > fire_delay)
	// update time buffers
	FOR(N_BUFFERS)
		if(time_buffer_enable[i])
		{
			time_buffer[i] += timeSinceLastFrame * quickness[i];
			if(time_buffer[i] > 1.0f)
				time_buffer_enable[i] = false;
		}

	recoil_pitch = 0.0f;
	// calculate actual recoil
	FOR(N_BUFFERS)
		if(time_buffer_enable[i])
			recoil_pitch += recoil(time_buffer[i]);
}
void Application :: Fire()
{
	// reinitialize bullet position and orientation
	n_bullet[nextbullet] -> setPosition
		(camera -> getDerivedPosition() + Vec3(0, offset_x, offset_y));
	n_bullet[nextbullet] -> setOrientation(camera -> getDerivedOrientation());
	++nextbullet; nextbullet %= BULLET_MAX;

	time_stack = 0.0f; 
	// handling recoil
	if(time_buffer_enable[current_recoil])
		time_since_last_shot = time_buffer
	time_buffer_enable[current_recoil] = true;
	time_buffer[current_recoil] = 0.0f;

	++current_recoil; current_recoil %= N_BUFFERS;
}
void Application :: update_bullets()
{
	FOR(BULLET_MAX)
		n_bullet[i] -> translate(0, 0, -timeSinceLastFrame * bullet_speed, Node::TS_LOCAL);
	if(trigged_pulled)
	{
		time_stack += timeSinceLastFrame;

		if (time_stack > fire_delay)
		{ 
			Fire();	
			next_bullet_ready = false;
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
