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
/*	for(size_t i = 0; i < sz; ++ i)
		Nodes[i]->translate(velocities[i] * timeSinceLastFrame);*/
	keyboard -> capture();
	mouse -> capture();
	n_master -> translate
	(
		n_yawpitch_ptr -> getOrientation() *
		translate *
		moving_speed *
		timeSinceLastFrame
	);
	assert(translate.length() <= 1.0f);
	loop_bullet();
	update_bullets();
	return ! stop;
	}

bool Application :: frameEnded(const FrameEvent & evt) { return true; }
bool Application :: frameStarted(const FrameEvent & evt) { return true; }