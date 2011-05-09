#include "stdafx.h"
#define TO_STR StringConverter :: toString
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text
	(
		TO_STR((int)(window -> getLastFPS())) + " Hz; "
<<<<<<< local
		//+ TO_STR(window -> getTriangleCount()) + " tri; "
		//+ TO_STR(window -> getBatchCount()) + " bat; "
		//+ "pos.y: " + TO_STR(position.y) + " "
		//+ "vel.y: " + TO_STR(velocity.y)
=======
		+ TO_STR(window -> getTriangleCount()) + " tri; "
		+ TO_STR(window -> getBatchCount()) + " bat; "
		+ "position: " + TO_STR(position.y) + " "
		+ "velocity: " + TO_STR(velocity.y)
>>>>>>> other
	);
	frame_time = evt.timeSinceLastFrame;
#define INTEGRATE
#ifdef INTEGRATE
	pos_prev = position;
	vel_prev = velocity;
	position = pos_prev + velocity * frame_time;
	velocity = vel_prev + 

#endif

	position += velocity * frame_time;
	velocity += gravity * frame_time;

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