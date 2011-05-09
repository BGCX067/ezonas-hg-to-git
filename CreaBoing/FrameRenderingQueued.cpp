#include "stdafx.h"
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat; "
		+ "position: " + TO_STR(position.y) + " "
		+ "velocity: " + TO_STR(velocity.y)
	);
	frame_time = evt.timeSinceLastFrame;
//#define INTEGRATE
#ifdef INTEGRATE // unfisinshed stuff, dont mind
	pos_prev = position;
	vel_prev = velocity;
	position = pos_prev + velocity * frame_time;
	velocity = vel_prev + 

#else
	position += velocity * frame_time;
	velocity += gravity * frame_time;
#endif

	if(position.y < 0.0f)
	{
		velocity.y *= -1;
		//position.y *= -1;
	}
	n_ball -> setPosition(position);

	return cam_ctrlr -> update();
}

void Application :: UpdatePhysics()
{
};

float interp_linear(float min, float max, float coeff) {return coeff * (max + min) / 2;}
float interp_square(float min, float max, float coeff) {return coeff * (max + min) / 2;}