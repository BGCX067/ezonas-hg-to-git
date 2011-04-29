#include "stdafx.h"
#define TO_STR StringConverter :: toString
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat; "
		+ "pos.y: " + TO_STR(position.y) + " "
		+ "vel.y: " + TO_STR(velocity.y)
	);
	frame_time = evt.timeSinceLastFrame;
	//n_ball -> translate(0,-frame_time * 10,0);
	if(position.y < ground_height)
	{
		n_ball -> setPosition(Vec3(0,0,0));
		//velocity = - gravity * frame_time;
	}
	UpdatePhysics();
	n_ball -> setPosition(position);

	return cam_ctrlr -> update();
}

void Application :: UpdatePhysics()
{
	if(velocity.y < 20)
	{
		velocity += gravity * frame_time;
		position += velocity * frame_time;
	}
	else
	{
		velocity = Vec3(0,0,0);
	}
};

float interp_linear(float min, float max, float coeff) {return coeff * (max + min) / 2;}
float interp_square(float min, float max, float coeff) {return coeff * (max + min) / 2;}