//#ifndef __APPLE__
#include "stdafx.h"
//#endif
template<> CameraController * Ogre :: Singleton <CameraController> :: ms_Singleton = 0;

void CameraController::setFollowedTarget(SceneNode * node) { n_target = node; }
SceneNode * CameraController :: getTargetNode() { return n_target; }
SceneNode * CameraController :: getMasterNode() { return n_master; }
//void CameraController :: setTarget(SceneNode * node) { n_target = node; }
void CameraController :: setEntity(Entity * ent) { character = ent; }

CameraController :: CameraController ():

#ifndef FOLDTHISFFS
	rotating_speed	(SGLT_APP -> GetFloat ("rotating_speed")),
	moving_speed	(SGLT_APP -> GetFloat ("moving_speed")),

	n_root			(Application :: getSingletonPtr() -> GetRSN()),

	n_master	    (n_root->	createChildSceneNode("master")),
	n_target	    (n_master->	createChildSceneNode("target")),	
	n_cam		    (n_target->	createChildSceneNode("cam")),
	n_yawpitch_ptr  (n_target),
	
	cam				(Application :: getSingletonPtr() -> GetCam()),
	//lasercast		(LaserCast :: Instantiate()),
	//bullet_tracer	(BulletTracer :: Instantiate()),
	stop			(false),
	frame_time		(Application :: getSingletonPtr() -> GetFT()),
	translate		(Vec3(0,0,0)),
	translate2		(Vec3(0,0,0)),
	offset			(SGLT_APP -> GetVect3("offset")),
	camera_mode		(3),
	rot(0.0f)
#endif
{
	n_cam -> setPosition(0,0,10);
	n_cam -> attachObject(cam);
	n_target -> setFixedYawAxis(true); // optional
	
#ifndef CONTROLS_AND_OTHER
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
		(inputmanager -> createInputObject(OISKeyboard, true));
	mouse = static_cast<Mouse *>
		(inputmanager -> createInputObject	(OISMouse, true));
	mouse -> setEventCallback(this);
	keyboard -> setEventCallback(this);
#endif
}
#define REINIT(node) { node -> setPosition(0,0,0); node->setOrientation(Quaternion()); }
void CameraController :: setCameraMode(int mode)
{
	/*
1. put a node (A) at the focus point you want to orbit around 			 # Target
2. make a child node (B) and set its position to (0,0, orbitdistance) 	 # cam
3. reset the orientation & position of the camera 						 #
4. attach the camera to node B 											 # cam
5. optionally setFixedYaw on node A 									 #
6. to orbit, yaw and pitch node A based on the x/y of the mouse 		 #
	// root master target yaw pitch cam	
	*/	// root master target yaw pitch cam	
	/* 
	default arch:
	root --> master --> target --> cam 
	yaw_pitch_ptr = target
	*/
	if(mode == camera_mode) return;

	n_master -> detachAllObjects(); n_master -> removeAllChildren();
	n_target -> detachAllObjects(); n_target -> removeAllChildren();
	n_cam	 -> detachAllObjects();	n_cam	 -> removeAllChildren();
	camera_mode = mode;

	REINIT (n_cam)
	REINIT (n_master)
	REINIT (cam)
	REINIT (n_target)
	switch (mode)
	{
	case 1:
		/////////////////////
		n_master -> addChild	(n_cam);
		n_cam	 -> attachObject(cam);
		/////////////////////
		n_target->setFixedYawAxis(false);
		n_yawpitch_ptr = n_cam;
		break;

	case 3:
		/////////////////////
		n_master -> addChild(n_target);
		n_target -> addChild(n_cam);

		n_target -> attachObject(character);
		n_cam->setPosition(0,0,10);
		n_cam->attachObject(cam);
		/////////////////////
		n_target->setFixedYawAxis(true);
		n_yawpitch_ptr = n_target;
		//character
		break;
	default:
		break;
	}
}
bool CameraController :: update ()
{
	keyboard -> capture();
	mouse -> capture();
	//n_cam -> getOrientation()
	n_master -> translate
	(
		n_yawpitch_ptr -> getOrientation() *
		translate *
		moving_speed *
		(* frame_time)
	);
		
	//cam ->setAutoTracking
	//cam -> lookAt(n_target->getPosition());

	if (translate.length() > 1.0f) exit(0xb00bbabe);
	return ! stop;
}
bool CameraController :: mouseMoved(const OIS::MouseEvent &e)
{
	n_yawpitch_ptr ->   yaw(Radian(- e.state.X.rel * rotating_speed), Ogre::Node::TS_WORLD);
	n_yawpitch_ptr -> pitch(Radian(- e.state.Y.rel * rotating_speed));
	return true;
}
bool CameraController :: mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	//if (mouse -> getMouseState() . buttonDown(MB_Left))
	//if (MB_Left == e.state.)
	//if (mouse -> getMouseState() . buttonDown(MB_Left))
	if (MB_Left == id)
		bullet_tracer -> Fire();
    return true;
}
bool CameraController :: mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id){ return true; }
bool CameraController :: keyPressed(const OIS::KeyEvent &e)
{
	switch(e.key)
	{
	case KC_ESCAPE: stop = true; break;
	//case KC_F1: setCameraMode(1); break;
	case KC_F2: setCameraMode(3); break;

	// index up, thumb left
	case KC_UP: case KC_W:						translate2.z -=  1.f; break;
	case KC_DOWN: case KC_S:					translate2.z +=  1.f; break;

	case KC_LEFT: case KC_A:					translate2.x -=  1.f; break;
	case KC_RIGHT: case KC_D:					translate2.x +=  1.f; break;
	//case KC_LEFT: case KC_A:					rot += .002f; break;
	//case KC_RIGHT: case KC_D:					rot -= .002f; break;

	case KC_PGUP: case KC_Q: case KC_LSHIFT:	translate2.y -=  1.f; break;
	case KC_PGDOWN: case KC_E: case KC_SPACE:	translate2.y +=  1.f; break;

	default: break;
	}
	translate = translate2;
	translate.normalise();
	OgreConsole::getSingleton().onKeyPressed(e);
	return true;
}
bool CameraController :: keyReleased(const OIS::KeyEvent &e)
{
	//Ogre :: Vector3 translate(0, 0, 0);
	switch(e.key)
	{
	case KC_ESCAPE:
		stop = true;
		break;

	case KC_UP: case KC_W:							translate2.z +=  1.f; break;
	case KC_DOWN: case KC_S:						translate2.z -=  1.f; break;

	//case KC_LEFT: case KC_A:						rot -= .002f; break;
	//case KC_RIGHT: case KC_D:						rot += .002f; break;
	case KC_LEFT: case KC_A:						translate2.x +=  1.f; break;
	case KC_RIGHT: case KC_D:						translate2.x -=  1.f; break;

	case KC_PGUP: case KC_Q: case KC_LSHIFT:		translate2.y +=  1.f; break;
	case KC_PGDOWN: case KC_E: case KC_SPACE:		translate2.y -=  1.f; break;

	default:
		break;
	}  
	translate = translate2;
	translate.normalise();
	return true;
}
CameraController :: ~ CameraController()
{
	inputmanager -> destroyInputObject(mouse);
	inputmanager -> destroyInputObject(keyboard);
	InputManager :: destroyInputSystem(inputmanager);
}
void CameraController :: setBulletTracer(BulletTracer * a) { bullet_tracer = a; }
