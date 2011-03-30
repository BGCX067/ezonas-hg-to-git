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
	bullet_tracer	(BulletTracer :: Instantiate()),
	_continue		(true),
	frame_time		(Application :: getSingletonPtr() -> GetFT()),
	translate		(Vec3(0,0,0))
{
	cam_pitch -> attachObject(cam);
	ParamList parameters;
	unsigned int windowHandle = 0;
	ostringstream windowHandleString;
	Application :: getSingletonPtr() -> GetRW() -> getCustomAttribute("WINDOW", & windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(make_pair("WINDOW", windowHandleString.str()));
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
		//(inputmanager -> createInputObject(OISKeyboard, false));
		(inputmanager -> createInputObject(OISKeyboard, true));
	mouse = static_cast<Mouse *>
		//(inputmanager -> createInputObject	(OISMouse, false));
		(inputmanager -> createInputObject	(OISMouse, true));
	mouse -> setEventCallback(this);
	keyboard -> setEventCallback(this);

}
FPersonCam :: ~ FPersonCam()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);

	//delete lasercast;
	//delete bullet_tracer;
}
bool FPersonCam :: update ()//float frame_time)
{
	keyboard -> capture();
	mouse -> capture();

	cam_node -> translate(
		cam_yaw -> getOrientation()
		* cam_pitch -> getOrientation()
		* translate
		* moving_speed
		* (* frame_time));

	lasercast -> update();//frame_time);
	bullet_tracer -> update();//frame_time);

	if (translate.length() > 1.0f)
	{	
		//cout << "dfs";
		exit(0xb00bbabe);
	}

	//cam_node -> translate(cam_yaw -> getOrientation() * cam_pitch -> getOrientation() *
	//translate * moving_speed * (* frame_time));
	//translate = Vec3 :: ZERO;
	return true;
}

// mouse ////////////////////////////////////
bool FPersonCam :: mouseMoved(const OIS::MouseEvent &e)
{
	//cam_yaw -> yaw(Radian(- mouse -> getMouseState().X.rel * rotating_speed));
	//cam_pitch -> pitch(Radian(- mouse -> getMouseState().Y.rel * rotating_speed));
	cam_yaw -> yaw(Radian(- e.state.X.rel * rotating_speed));
	cam_pitch -> pitch(Radian(- e.state.Y.rel * rotating_speed));
    return true;
}
bool FPersonCam :: mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	//if (mouse -> getMouseState() . buttonDown(MB_Left))
	//if (MB_Left == e.state.)
	//if (mouse -> getMouseState() . buttonDown(MB_Left))
	if (MB_Left == id)
		bullet_tracer -> Fire();
    return true;
}
bool FPersonCam :: mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
    return true;
}
// keyboard ////////////////////////////////////
bool FPersonCam :: keyPressed(const OIS::KeyEvent &e)
{
	//Ogre :: Vector3 translate(0, 0, 0);
	switch(e.key)
	{
	case KC_ESCAPE:
		_continue = false;
		return false;
		break;

	//case KC_W:
	//	translate += Ogre :: Vector3(0, 0, -1);
	//	break;

	//case KC_S:
	//	translate += Ogre :: Vector3(0, 0, 1);
	//	break;

	//case KC_A:
	//	translate += Ogre :: Vector3(-1, 0, 0);
	//	break;

	//case KC_D:
	//	translate += Ogre :: Vector3(1, 0, 0);
	//	break;

	//case KC_Q:
	//	translate += Ogre :: Vector3(0, -1, 0);
	//	break;

	//case KC_E:
	//	translate += Ogre :: Vector3(0, 1, 0);
	//	break;
	case KC_UP:
	case KC_W:
		translate.z = - 1.f;
		break;

	case KC_DOWN:
	case KC_S:
		translate.z =  1.f;
		break;

	case KC_LEFT:
	case KC_A:
		translate.x = - 1.f;
		break;

	case KC_RIGHT:
	case KC_D:
		translate.x =  1.f;
		break;

	case KC_PGUP:
	case KC_Q:
		translate.y = - 1.f;
		break;

	case KC_PGDOWN:
	case KC_E:
		translate.y =  1.f;
		break;
	default:
		break;
	}
	translate.normalise();
    return true;
}
bool FPersonCam :: keyReleased(const OIS::KeyEvent &e)
{
	//Ogre :: Vector3 translate(0, 0, 0);
	switch(e.key)
	{
	case KC_UP:
	case KC_W:
		translate.z = 0.0f;
		break;

	case KC_DOWN:
	case KC_S:
		translate.z = 0.0f;
		break;

	case KC_LEFT:
	case KC_A:
		translate.x = 0.0f;
		break;

	case KC_RIGHT:
	case KC_D:
		translate.x = 0.0f;
		break;

	case KC_PGUP:
	case KC_Q:
		translate.y = 0.0f;
		break;

	case KC_PGDOWN:
	case KC_E:
		translate.y = 0.0f;
		break;
	default:
		break;
	}  
	//translate.normalise();
	return true;
}