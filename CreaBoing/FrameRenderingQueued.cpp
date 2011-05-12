#include "stdafx.h"
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat; "
		+ "pos: " + TO_STR(position.x) + " " + TO_STR(position.y) + " " + TO_STR(position.z) + " "
		+ "vel: " + TO_STR(velocity.x) + " " + TO_STR(velocity.y) + " " + TO_STR(velocity.z) + " "
	);
	frame_time = evt.timeSinceLastFrame;
	UpdatePhysics();
	return cam_ctrlr -> update();
}

void Application :: UpdatePhysics()
{
//#define INTEGRATE
//#define INTEGRATE_DERIVATE_NEW
//#define INTEGRATE_DERIVATE_PRIOR
	if(position.y < 0.0f)
		forces = - velocity;
	else
		forces = gravity;

#ifdef INTEGRATE_DERIVATE_PRIOR
	velocity = vel_prev + pos_prev * frame_time;
	position = pos_prev + vel_prev * frame_time;
	pos_prev = position;
	vel_prev = velocity;

#elif defined INTEGRATE_DERIVATE_NEW
	velocity = vel_prev + position * frame_time;
	position = pos_prev + velocity * frame_time;
	pos_prev = position;
	vel_prev = velocity;
#else
	velocity += forces * frame_time;
	position += velocity * frame_time;
#endif
	n_ball -> setPosition(position);

};

float interp_linear(float min, float max, float coeff) {return coeff * (max + min) / 2;}
float interp_square(float min, float max, float coeff) {return coeff * (max + min) / 2;}