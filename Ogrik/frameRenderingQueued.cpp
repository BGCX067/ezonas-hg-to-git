#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
// keyboard and mouse capturing
	keyboard -> capture();
	if (keyboard -> isKeyDown(KC_ESCAPE)) return false;
	Ogre :: Vector3 translate(0, 0, 0);
	if (keyboard -> isKeyDown(KC_W)) translate += Ogre :: Vector3(0, 0, -1);
	if (keyboard -> isKeyDown(KC_S)) translate += Ogre :: Vector3(0, 0, 1);

	if (keyboard -> isKeyDown(KC_A)) translate += Ogre :: Vector3(-1, 0, 0);
	if (keyboard -> isKeyDown(KC_D)) translate += Ogre :: Vector3(1, 0, 0);

	if (keyboard -> isKeyDown(KC_Q)) translate += Ogre :: Vector3(0, -1, 0);
	if (keyboard -> isKeyDown(KC_E)) translate += Ogre :: Vector3(0, 1, 0);

#define FPS_CAM2
	mouse -> capture();
#ifdef FPS_CAM
	camera -> moveRelative(translate * evt.timeSinceLastFrame * moving_speed);
	camera -> yaw(Ogre :: Radian(mouse -> getMouseState().X.rel * rotating_speed));
	camera -> pitch(Ogre :: Radian(mouse -> getMouseState().Y.rel * rotating_speed));
#else
	fpersoncam -> update
	(
		mouse -> getMouseState().X.rel * rotating_speed,
		mouse -> getMouseState().Y.rel * rotating_speed,
		translate * evt.timeSinceLastFrame * moving_speed
	);
#endif
//	cursor_ray = camera -> getCameraToViewportRay
	//raycast -> update();
	//laserdot -> setPosition(laser_hit);
	bullet_t -> translate(evt.timeSinceLastFrame * bullet_speed, 0, 0);

	bbchain -> updateChainElement
		(0, 0, BillboardChain::Element(laser_hit, laser_width, 0, ColourValue()));

	return true;
}
