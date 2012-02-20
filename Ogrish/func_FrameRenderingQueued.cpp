#include "stdafx.h"

// ############################# frameStarted #############################
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
	for(size_t i = 0; i < sz; ++ i)
		Nodes[i]->translate(velocities[i] * timeSinceLastFrame);

	//check_collisions();
	handle_bullet();

	lasercast -> update();
	bullet_tracer -> update();

	return cam_ctrlr -> update();//evt.timeSinceLastFrame);
}

bool Application :: frameEnded(const FrameEvent & evt) { return true; }
bool Application :: frameStarted(const FrameEvent & evt) { return true; }