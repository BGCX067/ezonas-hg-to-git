//#ifndef __APPLE__
#include "stdafx.h"
//#endif
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat"
	);
	frame_time = evt.timeSinceLastFrame;

	//Entities[1]->
	//transf.
	return cam_ctrlr -> update();//evt.timeSinceLastFrame);
}

