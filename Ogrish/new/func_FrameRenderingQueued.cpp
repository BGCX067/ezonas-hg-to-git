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
	size_t sz = velocities.size();
	for(size_t i = 0; i < sz; ++ i)
		Nodes[i]->translate(velocities[i] * frame_time);

	//check_collisions();
	handle_bullet();
	// current_ent_raycast;
	// last_entity_raycast;
	current_ent_raycast = lasercast->getEntityCheck();
	if (current_ent_raycast == last_entity_raycast);
	else
	{
		static_cast<SceneNode*>(last_entity_raycast->getParentNode())->showBoundingBox(false);
		static_cast<SceneNode*>(current_ent_raycast->getParentNode())->showBoundingBox(true);
	}

	lasercast -> update();
	bullet_tracer -> update();

	return cam_ctrlr -> update();//evt.timeSinceLastFrame);
}

bool Application :: frameEnded(const FrameEvent & evt) { return true; }
bool Application :: frameStarted(const FrameEvent & evt) { return true; }