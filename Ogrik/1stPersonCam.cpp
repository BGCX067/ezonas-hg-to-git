#include "stdafx.h"

// void FPersonCam :: update (float yaw, float pitch, Vec3 & vect)
bool FPersonCam :: update (float frame_time)
{
	keyboard -> capture();
	if (keyboard -> isKeyDown(KC_ESCAPE)) return false;
	Ogre :: Vector3 translate(0, 0, 0);
	if (keyboard -> isKeyDown(KC_W)) translate += Ogre :: Vector3(0, 0, -1);
	if (keyboard -> isKeyDown(KC_S)) translate += Ogre :: Vector3(0, 0, 1);

	if (keyboard -> isKeyDown(KC_A)) translate += Ogre :: Vector3(-1, 0, 0);
	if (keyboard -> isKeyDown(KC_D)) translate += Ogre :: Vector3(1, 0, 0);

	if (keyboard -> isKeyDown(KC_Q)) translate += Ogre :: Vector3(0, -1, 0);
	if (keyboard -> isKeyDown(KC_E)) translate += Ogre :: Vector3(0, 1, 0);

	mouse -> capture();
	//fpersoncam -> update
	//(
	//	,
	//	,
	//	translate * evt.timeSinceLastFrame * moving_speed
	//);
//
	cam_yaw -> yaw(Radian(mouse -> getMouseState().X.rel * rotating_speed));
	cam_pitch -> pitch(Radian(mouse -> getMouseState().Y.rel * rotating_speed));
	cam_node -> translate
	(cam_yaw -> getOrientation() * cam_pitch -> getOrientation() *
	translate * moving_speed * frame_time);

	lasercast -> update(frame_time);
	return true;
}

FPersonCam :: FPersonCam(Camera * camera, SceneNode * rootscnd, RenderWindow * _window):

	rotating_speed	(ConfMgr :: sglt() -> GetFloat("rotating_speed")),
	moving_speed	(ConfMgr :: sglt() -> GetFloat("moving_speed")),
	cam_node		(rootscnd -> createChildSceneNode		("cam_node")),
	cam_yaw			(cam_node -> createChildSceneNode		("cam_yaw")),
	cam_pitch		(cam_yaw -> createChildSceneNode		("cam_pitch")),
	cam_roll		(cam_pitch -> createChildSceneNode		("cam_roll")),
	cam				(camera),
	lasercast		(new LaserCast(camera, Application :: GetScMgr()))

{
	cam_roll -> attachObject(cam);
	cam_node -> setPosition(100, 0, 0);
	cam_node -> pitch(Radian(Degree(-20)));
/* ### Inputs ########################################################## */
	ParamList parameters;

	unsigned int windowHandle = 0;
	ostringstream windowHandleString;

	_window -> getCustomAttribute("WINDOW", & windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(make_pair("WINDOW", windowHandleString.str()));
// those settings unhide the cursor (from ogre's wiki snippets)
#if defined OIS_WIN32_PLATFORM
	parameters.insert(make_pair(string("w32mouse"), string("DISCL_FOREGROUND" )));
	parameters.insert(make_pair(string("w32mouse"), string("DISCL_NONEXCLUSIVE")));
	parameters.insert(make_pair(string("w32keyboard"), string("DISCL_FOREGROUND")));
	parameters.insert(make_pair(string("w32keyboard"), string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	parameters.insert(make_pair(string("x11mouse_grab"), string("false")));
	parameters.insert(make_pair(string("x11mouse_hide"), string("false")));
	parameters.insert(make_pair(string("x11keyboard_grab"), string("false")));
	parameters.insert(make_pair(string("XAutoRepeatOn"), string("true")));
#endif
/* ### Inputs Objects ################################################## */
	inputmanager = InputManager :: createInputSystem(parameters);
	keyboard = static_cast<Keyboard *>
	(inputmanager -> createInputObject(OISKeyboard, false));
	mouse = static_cast<Mouse *>
	(inputmanager -> createInputObject	(OISMouse, false));
}
FPersonCam :: ~ FPersonCam()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);
	delete lasercast;
}