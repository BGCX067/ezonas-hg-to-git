#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const Ogre::FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat"
	);
	frame_time = evt.timeSinceLastFrame;
	size_t sz = velocities.size();
	for(size_t i = 0; i < sz; ++ i)
		Nodes[i]->translate(velocities[i] * frame_time);
	//transf.set
	//handle_bullet();
	
	check_collisions();

	lasercast -> update();
	bullet_tracer -> update();


	return cam_ctrlr -> update();//evt.timeSinceLastFrame);
}

#endif