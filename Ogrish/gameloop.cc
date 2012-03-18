#include "stdafx.h"
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat"
	);
	//size_t sz = velocities.size();
	//for(size_t i = 0; i < sz; ++ i)
	//	Nodes[i]->translate(velocities[i] * timeSinceLastFrame);*/
	keyboard -> capture();
	mouse -> capture();
	timeSinceLastFrame = evt.timeSinceLastFrame;

	n_master -> translate
		(n_yawpitch_ptr -> getOrientation() * translate * moving_speed * timeSinceLastFrame);
	assert(translate.length() <= 1.0f);
	update_physics();
	update_bullets();
	n_recoil->setOrientation(
		0.770151153f * Math::Cos(recoil_pitch*.5f),
		0.770151153f * Math::Sin(recoil_pitch*.5f),0,0);
	update_laser();
		
	return ! stop;
}
void Application :: diagnose()
{
	LOGMSG("----- diagnose start -----");
	for(auto iter = diagnose_vect.begin(); iter!=diagnose_vect.end(); ++iter)
		LOGMSG(iter->first + " = " +str_vect(iter->second));
	for(auto iter = diagnose_float.begin(); iter!=diagnose_float.end(); ++iter)
		LOGMSG(iter->first + " = " +TO_STR(iter->second));
	LOGMSG("----- diagnose end -----");
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
