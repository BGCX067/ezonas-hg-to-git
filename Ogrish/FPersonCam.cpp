#include "stdafx.h"
template<> FPersonCam * Ogre :: Singleton <FPersonCam> :: ms_Singleton = 0;

// FPersonCam :: FPersonCam
FPersonCam :: FPersonCam ():


	rotating_speed	(ConfMgr :: getSingletonPtr() -> GetFloat ("rotating_speed")),
	moving_speed	(ConfMgr :: getSingletonPtr() -> GetFloat ("moving_speed")),
	cam_node		(Application :: getSingletonPtr() -> GetRSN() -> createChildSceneNode ("cam_node")),
	cam_yaw			(cam_node -> createChildSceneNode ("cam_yaw")),
	cam_pitch		(cam_yaw -> createChildSceneNode ("cam_pitch")),
	cam				(Application :: getSingletonPtr() -> GetCam()),
	lasercast		(LaserCast :: Instantiate()),
	bullet_tracer	(BulletTracer :: Instantiate())
{
#define USE_NODES
#ifdef USE_NODES
	//cam_roll -> attachObject(cam);
	cam_pitch -> attachObject(cam);
#else
	Application :: getSingletonPtr() -> GetScMgr() -> getRootSceneNode() -> attachObject(cam);
#endif
	ParamList parameters;
	unsigned int windowHandle = 0;
	ostringstream windowHandleString;
	Application :: getSingletonPtr() -> GetRW() -> getCustomAttribute("WINDOW", & windowHandle);
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
// FPersonCam :: ~ FPersonCam
FPersonCam :: ~ FPersonCam()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);

	//delete lasercast;
	//delete bullet_tracer;
}
// FPersonCam :: update
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

	if (mouse -> getMouseState() . buttonDown(MB_Left))
		bullet_tracer -> Fire();
	mouse -> capture();

#ifdef USE_NODES
	translate.normalise();
	if (translate.length() > 1.0f)
		exit( 0xb00bbabe);

	cam_yaw -> yaw(Radian(- mouse -> getMouseState().X.rel * rotating_speed));
	cam_pitch -> pitch(Radian(- mouse -> getMouseState().Y.rel * rotating_speed));
	cam_node -> translate(cam_yaw -> getOrientation() * cam_pitch -> getOrientation() *
	translate * moving_speed * frame_time);
#else
	cam -> yaw(Radian(- mouse -> getMouseState().X.rel * rotating_speed));
	cam -> pitch(Radian(- mouse -> getMouseState().Y.rel * rotating_speed));
	cam -> moveRelative(translate);
#endif
	lasercast -> update(frame_time);
	bullet_tracer -> update(frame_time);

	return true;
}

//FPersonCam * FPersonCam :: sglt()
//{
//	static FPersonCam _;
//	return & _;
//}