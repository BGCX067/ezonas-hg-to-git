#include "stdafx.h"
template<> CameraController * Ogre :: Singleton <CameraController> :: ms_Singleton = 0;
void CameraController :: setCamPosition (Vec3 dada) { cam_node -> setPosition(dada); }
SceneNode * CameraController :: GetNode () { return cam_node; }
CameraController :: CameraController ():


	rotating_speed	(ConfMgr :: getSingletonPtr() -> GetFloat ("rotating_speed")),
	moving_speed	(ConfMgr :: getSingletonPtr() -> GetFloat ("moving_speed")),
	vel_step		(ConfMgr :: getSingletonPtr() -> GetFloat ("vel_step")),
	cam_node		(Application :: getSingletonPtr() -> GetRSN() -> createChildSceneNode ("cam_node")),
	cam_yaw			(cam_node -> createChildSceneNode ("cam_yaw")),
	cam_pitch		(cam_yaw -> createChildSceneNode ("cam_pitch")),
	cam				(Application :: getSingletonPtr() -> GetCam()),
//	lasercast		(LaserCast :: Instantiate()),
//	bullet_tracer	(BulletTracer :: Instantiate()),
	stop			(false),
	frame_time		(Application :: getSingletonPtr() -> GetFT()),
	translate		(Vec3(0,0,0)),
	translate2		(Vec3(0,0,0)),
	velocity		(SGLT_APP -> GetVelocityAddress()),
	vel_modifier	(Vec3(0,0,0)),
	key_pushed		(false)
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
CameraController :: ~ CameraController()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);

	//delete lasercast;
	//delete bullet_tracer;
}
bool CameraController :: update ()//float frame_time)
{
	keyboard -> capture();
	mouse -> capture();

	cam_node -> translate(
		cam_yaw -> getOrientation()
		* cam_pitch -> getOrientation()
		* translate * moving_speed * (* frame_time));

	* velocity += vel_modifier;
	if(time_stack < 0.1f && key_pushed == false)
	{
		time_stack = 0.f;
	}
	if (time_stack > 0.1f) key_pushed = false;
	time_stack += * frame_time;

	if (translate.length() > 1.0f) exit(0xb00bbabe);
	return ! stop;
}
bool CameraController :: keyPressed(const OIS::KeyEvent &e)
{	
	key_pushed = true;
	switch(e.key)
	{
	case KC_ESCAPE:
		stop = true; break;

	case KC_UP: case KC_W:		vel_modifier . z -=  vel_step; break;
	case KC_DOWN: case KC_S:	vel_modifier . z +=  vel_step; break;
	case KC_LEFT: case KC_A:	vel_modifier . x -=  vel_step; break;
	case KC_RIGHT: case KC_D:	vel_modifier . x +=  vel_step; break;
	case KC_PGUP: case KC_Q:	vel_modifier . y -=  vel_step; break;
	case KC_PGDOWN: case KC_E:	vel_modifier . y +=  vel_step; break;
	//case KC_UP: case KC_W:		translate2.z -=  1.f; break;
	//case KC_DOWN: case KC_S:	translate2.z +=  1.f; break;
	//case KC_LEFT: case KC_A:	translate2.x -=  1.f; break;
	//case KC_RIGHT: case KC_D:	translate2.x +=  1.f; break;
	//case KC_PGUP: case KC_Q:	translate2.y -=  1.f; break;
	//case KC_PGDOWN: case KC_E:	translate2.y +=  1.f; break;

	default: break;
	}
	translate = translate2;
	translate.normalise();
    return true;
}
bool CameraController :: keyReleased(const OIS::KeyEvent &e)
{
	key_pushed = false;
	switch(e.key)
	{
	case KC_ESCAPE:
		stop = true;
		break;

	case KC_UP: case KC_W:		vel_modifier . z +=  vel_step; break;
	case KC_DOWN: case KC_S:	vel_modifier . z -=  vel_step; break;
	case KC_LEFT: case KC_A:	vel_modifier . x +=  vel_step; break;
	case KC_RIGHT: case KC_D:	vel_modifier . x -=  vel_step; break;
	case KC_PGUP: case KC_Q:	vel_modifier . y +=  vel_step; break;
	case KC_PGDOWN: case KC_E:	vel_modifier . y -=  vel_step; break;

	//case KC_UP: case KC_W:		translate2.z +=  1.f; break;
	//case KC_DOWN: case KC_S:	translate2.z -=  1.f; break;
	//case KC_LEFT: case KC_A:	translate2.x +=  1.f; break;
	//case KC_RIGHT: case KC_D:	translate2.x -=  1.f; break;
	//case KC_PGUP: case KC_Q:	translate2.y +=  1.f; break;
	//case KC_PGDOWN: case KC_E:	translate2.y -=  1.f; break;

	default:
		break;
	}  
	translate = translate2;
	translate.normalise();
	return true;
}
bool CameraController :: mouseMoved(const OIS::MouseEvent &e)
{
	//cam_yaw -> yaw(Radian(- e.state.X.rel * rotating_speed));
	//cam_pitch -> pitch(Radian(- e.state.Y.rel * rotating_speed));
    return true;
}
bool CameraController :: mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	if (MB_Left == id);
    return true;
}
bool CameraController :: mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{ return true; }
