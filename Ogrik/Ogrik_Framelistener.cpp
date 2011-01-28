#include "stdafx.h"

OgrikFrameListener :: OgrikFrameListener(RenderWindow* win, Camera* cam)
{
	_Cam = cam;
	_movementspeed = 50.0f;

	ParamList parameters;
	unsigned int windowHandle = 0;
	ostringstream windowHandleString;

	win->getCustomAttribute("WINDOW", &windowHandle);
	windowHandleString << windowHandle;
	parameters.insert(make_pair("WINDOW", windowHandleString.str()));

	_InputManager = InputManager::createInputSystem(parameters);
	_Keyboard = static_cast<Keyboard*>(_InputManager->createInputObject( OISKeyboard, false ));
	_Mouse = static_cast<Mouse*>(_InputManager->createInputObject( OISMouse, false ));
}
OgrikFrameListener :: ~ OgrikFrameListener()
{
	_InputManager->destroyInputObject(_Keyboard);
	_InputManager->destroyInputObject(_Mouse);
	InputManager::destroyInputSystem(_InputManager);
}
bool OgrikFrameListener :: frameStarted(const FrameEvent & evt)
{
	_Keyboard->capture();
	if(_Keyboard->isKeyDown(KC_ESCAPE))
	{
		return false;
	}

	Ogre :: Vector3 translate(0,0,0);
	if(_Keyboard->isKeyDown(KC_W))
	{
		translate += Ogre :: Vector3(0,0,-1);
	}
	if(_Keyboard->isKeyDown(KC_S))
	{
		translate += Ogre :: Vector3(0,0,1);
	}
	if(_Keyboard->isKeyDown(KC_A))
	{
		translate += Ogre :: Vector3(-1,0,0);
	}
	if(_Keyboard->isKeyDown(KC_D))
	{
		translate += Ogre :: Vector3(1,0,0);
	}
	_Cam->moveRelative(translate*evt.timeSinceLastFrame * _movementspeed);

	_Mouse->capture();
	float rotX = _Mouse->getMouseState().X.rel * evt.timeSinceLastFrame* -1;
	float rotY = _Mouse->getMouseState().Y.rel * evt.timeSinceLastFrame * -1;


	_Cam->yaw(Radian(rotX));
	_Cam->pitch(Radian(rotY));


	return true;
}

