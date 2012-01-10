#ifndef __APPLE__
#include "stdafx.h"
#endif
template<> CameraController * Ogre :: Singleton <CameraController> :: ms_Singleton = 0;
CameraController :: CameraController ():

#ifndef FOLDTHISFFS
	rotating_speed	(SGLT_APP -> GetFloat ("rotating_speed")),
	moving_speed	(SGLT_APP -> GetFloat ("moving_speed")),

	n_root			(Application :: getSingletonPtr() -> GetRSN()),

#define ORBIT
#ifdef ORBIT
	n_master	(n_root->	createChildSceneNode("master")),
	n_target	(n_master->	createChildSceneNode("target")),	
	n_cam		(n_target->	createChildSceneNode("cam")),
#else
	n_master		(n_root		-> createChildSceneNode ("master")),

	n_target		(n_master	-> createChildSceneNode ("target")),
	n_yaw			(n_target	-> createChildSceneNode ("yaw")),
	n_pitch			(n_yaw		-> createChildSceneNode ("pitch")),
	n_cam			(n_pitch	-> createChildSceneNode ("cam")),
#endif
	cam				(Application :: getSingletonPtr() -> GetCam()),
	lasercast		(LaserCast :: Instantiate()),
	bullet_tracer	(BulletTracer :: Instantiate()),
	stop			(false),
	frame_time		(Application :: getSingletonPtr() -> GetFT()),
	translate		(Vec3(0,0,0)),
	translate2		(Vec3(0,0,0)),
	offset			(SGLT_APP -> GetVect3("offset")),
	camera_mode		("1st")
#endif
{
	/*
1. put a node (A) at the focus point you want to orbit around 			 # Target
2. make a child node (B) and set its position to (0,0, orbitdistance) 	 # cam
3. reset the orientation & position of the camera 						 #
4. attach the camera to node B 											 # cam
5. optionally setFixedYaw on node A 									 #
6. to orbit, yaw and pitch node A based on the x/y of the mouse 		 #
	*/
	// root master target yaw pitch cam	

	//n_master = n_root->createChildSceneNode("master");
	//n_target = n_master->createChildSceneNode("target");	
	//n_cam = n_target->createChildSceneNode("cam");
	n_cam->setPosition(0,0,10);
	n_cam->attachObject(cam);
	n_target->setFixedYawAxis(true); // optional


	//n_master -> addChild(n_target);   //"master"  
	//n_cam -> translate(0,0, 10);		//"target"  
	//n_target -> addChild(n_cam);		//"cam"     
										//"yawpitch"
	
	//n_master->translate(SGLT_APP->GetVect3("cam_master"));
	//n_cam->setFixedYawAxis(true);
	//n_cam -> translate(offset); 
	//cam->setAutoTracking(true, n_target, offset);

#ifndef FOLDTHISFFS

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

void CameraController :: setCameraMode(string str)
{
	// root master target yaw pitch cam	
	if(str == camera_mode) return;
	if (camera_mode == "1st") {
		camera_mode = "3rd";
		//n_cam -> translate(-offset);
		return;
	}
	if (camera_mode == "3rd"){
		camera_mode = "1st";
		//n_cam -> translate(offset); 
		return;
	}
}
bool CameraController :: update ()
{
	keyboard -> capture();
	mouse -> capture();

	//n_cam -> getOrientation()
	n_master -> translate(
		n_target -> getOrientation() * // warning, comment this if you want to blabla front of
		//* n_pitch -> getOrientation()
		//*
		//n_target -> getOrientation() *
		translate * moving_speed * (* frame_time));
		
	//cam ->setAutoTracking
	//cam -> lookAt(n_target->getPosition());
	lasercast -> update();
	bullet_tracer -> update();

	if (translate.length() > 1.0f) exit(0xb00bbabe);
	return ! stop;
}
bool CameraController :: mouseMoved(const OIS::MouseEvent &e)
{
#define FIRSTPERSON
#ifdef FIRSTPERSON
	n_target ->   yaw(Radian(- e.state.X.rel * rotating_speed), Ogre::Node::TS_WORLD);
	n_target -> pitch(Radian(- e.state.Y.rel * rotating_speed));
	//cam ->     yaw(Radian(- e.state.X.rel * rotating_speed));
	//cam -> pitch(Radian(- e.state.Y.rel * rotating_speed));
#endif
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
	case KC_F1: setCameraMode("1st"); break;
	case KC_F2: setCameraMode("3rd"); break;

	// index up, thumb left
	case KC_UP: case KC_W:							translate2.z -=  1.f; break;
	case KC_DOWN: case KC_S:						translate2.z +=  1.f; break;

	case KC_LEFT: case KC_A:						translate2.x -=  1.f; break;
	case KC_RIGHT: case KC_D:						translate2.x +=  1.f; break;

	case KC_PGUP: case KC_Q: case KC_LSHIFT:		translate2.y -=  1.f; break;
	case KC_PGDOWN: case KC_E: case KC_SPACE:		translate2.y +=  1.f; break;

	default: break;
	}
	translate = translate2;
	translate.normalise();
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
void CameraController::setFollowedTarget(SceneNode * node) { n_target = node; }
SceneNode * CameraController :: getTargetNode() { return n_target; }
SceneNode * CameraController :: getMasterNode() { return n_master; }
