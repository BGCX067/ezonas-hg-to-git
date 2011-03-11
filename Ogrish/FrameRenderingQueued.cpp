#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
// keyboard and mouse capturing
	// raycast -> execute();
//	cursor_ray = camera -> getCameraToViewportRay
	return fpersoncam -> update(evt.timeSinceLastFrame);
}

