#include "stdafx.h"
#define TO_STR StringConverter :: toString
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
	//n_ball -> translate(0,-frame_time * 10,0);
	if(n_ball -> getPosition().y < ground_height)
	{
		n_ball -> setPosition(Vec3(0,0,0));
		//velocity = - gravity;
	}
	UpdatePhysics();
	n_ball -> setPosition(position);

	return cam_ctrlr -> update();
}


void Application :: UpdatePhysics()
{
	velocity += gravity * frame_time; // * 0.00001;
	position += velocity * frame_time; // * 0.00001;
};