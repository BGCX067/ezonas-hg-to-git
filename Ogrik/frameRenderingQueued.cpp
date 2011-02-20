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

	camera -> moveRelative(translate * evt.timeSinceLastFrame * moving_speed);

#ifdef FPS_CAM
	mouse -> capture();
	//float rotX = mouse -> getMouseState().X.rel * evt.timeSinceLastFrame * -1 * rotating_speed;
	//float rotY = mouse -> getMouseState().Y.rel * evt.timeSinceLastFrame * -1 * rotating_speed;
	float rotX = mouse -> getMouseState().X.rel * -1 * rotating_speed;
	float rotY = mouse -> getMouseState().Y.rel * -1 * rotating_speed;
// camera movements
	camera -> yaw(Ogre :: Radian(rotX));
	camera -> pitch(Ogre :: Radian(rotY));
//	cursor_ray = camera -> getCameraToViewportRay

	raycast -> update();
	laserdot -> setPosition(laser_hit);
	
#endif

	bbchain -> updateChainElement
		(0, 1, BillboardChain::Element(laser_hit, laser_width, 0, ColourValue(1, 0, 0)));

	return true;
}
