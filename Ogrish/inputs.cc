#include "stdafx.h"

void Application :: init_inputs()
{
	OIS::ParamList parameters;
	unsigned int windowHandle = 0;
	ostringstream windowHandleString;
	 window -> getCustomAttribute("WINDOW", & windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(make_pair("WINDOW", windowHandleString.str()));
	parameters.insert(make_pair("WINDOW", windowHandleString.str()));
// those settings unhide the cursor (from ogre's wiki snippets)
#if defined OIS_WIN32_PLATFORM
	parameters.insert(make_pair(string("w32mouse"), 	string("DISCL_FOREGROUND" )));
	parameters.insert(make_pair(string("w32mouse"), 	string("DISCL_NONEXCLUSIVE")));
	parameters.insert(make_pair(string("w32keyboard"), 	string("DISCL_FOREGROUND")));
	parameters.insert(make_pair(string("w32keyboard"), 	string("DISCL_NONEXCLUSIVE")));
#elif defined OIS_LINUX_PLATFORM
	parameters.insert(make_pair(string("x11mouse_grab"), 	string("false")));
	parameters.insert(make_pair(string("x11mouse_hide"), 	string("false")));
	parameters.insert(make_pair(string("x11keyboard_grab"), string("false")));
	parameters.insert(make_pair(string("XAutoRepeatOn"), 	string("true")));
#endif
/* ### Inputs Objects ################################################## */
	 inputmanager = OIS::InputManager :: createInputSystem(parameters);
	 keyboard = static_cast<OIS::Keyboard *>
		(inputmanager -> createInputObject(OIS::OISKeyboard, true));
	 mouse = static_cast<OIS::Mouse *>
		(inputmanager -> createInputObject	(OIS::OISMouse, true));
	 mouse -> setEventCallback(this);
	 keyboard -> setEventCallback(this);

}
bool Application :: mouseMoved		(const OIS::MouseEvent &e)
{
	n_yawpitch_ptr ->   yaw(Radian(- e.state.X.rel * rotating_speed), Ogre::Node::TS_WORLD);
	n_yawpitch_ptr -> pitch(Radian(- e.state.Y.rel * rotating_speed));
	return true;
}
bool Application :: mousePressed	(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	using namespace OIS;
	if (MB_Left == id) trigger_pull();
    return true;
}
bool Application :: mouseReleased	(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	using namespace OIS;
	if (MB_Left == id) trigger_release();
	return true;
}
bool Application :: keyPressed		(const OIS::KeyEvent &e)
{
	using namespace OIS;
	switch(e.key)
	{
	case KC_ESCAPE: stop = true; break;
	//case KC_F1: setCameraMode(1); break;
	case KC_F2: setCameraMode(1); break;
	case KC_F3: setCameraMode(3); break;
	case KC_F5: diagnose(); break;

	// index up, thumb left
	case KC_UP: case KC_W:						translate2.z -=  1.f; break;
	case KC_DOWN: case KC_S:					translate2.z +=  1.f; break;
	case KC_F4:
//		mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)
//			->setColourOperationEx(Ogre::LBX_SOURCE1, Ogre::LBS_MANUAL, Ogre::LBS_CURRENT, colorval);	
		//mat->getTechnique(0)->getPass(0)->getTextureUnitState(0)
		//	->setColourOperationEx(Ogre::LBX_SOURCE1,LBS_TEXTURE,LBS_CURRENT,colorval1,colorval2);
				break;
	case KC_LEFT: case KC_A:					translate2.x -=  1.f; break;
	case KC_RIGHT: case KC_D:					translate2.x +=  1.f; break;
	//case KC_LEFT: case KC_A:					rot += .002f; break;
	//case KC_RIGHT: case KC_D:					rot -= .002f; break;

	case KC_PGUP: case KC_Q: case KC_LSHIFT:	translate2.y -=  1.f; break;
	case KC_PGDOWN: case KC_E: case KC_SPACE:	translate2.y +=  1.f; break;
	case KC_MINUS:
		if(camera ->getFOVy() > Degree(10.f))
			camera ->setFOVy(camera ->getFOVy() - Radian(timeSinceLastFrame) *20.f);
		break;
	case KC_EQUALS:
		if(camera ->getFOVy() < Degree(120.f))
			camera ->setFOVy(camera ->getFOVy() + Radian(timeSinceLastFrame) *20.f);
		break;
	default: break;
	}
	translate = translate2;
	translate.normalise();
	console -> onKeyPressed(e);
	return true;
}
bool Application :: keyReleased	(const OIS::KeyEvent &e)
{
	using namespace OIS;
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
