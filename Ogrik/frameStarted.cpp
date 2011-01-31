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
	camera -> moveRelative(translate * evt.timeSinceLastFrame * 20.0f);
	
#ifdef FPS_CAM
	mouse -> capture();
	float rotX = mouse -> getMouseState().X.rel *
		evt.timeSinceLastFrame * -1;
	float rotY = mouse -> getMouseState().Y.rel *
		evt.timeSinceLastFrame * -1;
// camera movements
	camera -> yaw(Ogre :: Radian(rotX));
	camera -> pitch(Ogre :: Radian(rotY));
#endif
	// rays
	cursor_ray = camera -> getCameraToViewportRay
	(
		mouse -> getMouseState() . X.abs /
		(float) mouse -> getMouseState() . width, 
		mouse -> getMouseState() . Y.abs /
		(float) mouse -> getMouseState() . height
	);
	RSQ -> execute();
	return true;
}