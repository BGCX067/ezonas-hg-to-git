#include "stdafx.h"

OgrikFrameListener :: OgrikFrameListener
(SceneManager * _scmgr,
	Camera * _cam,
	InputManager * _inputmanager,
	Mouse * _mouse,
	Keyboard * _kb):

	scenemanager(_scmgr),
	inputmanager(_inputmanager),
	mouse(_mouse),
	keyboard(_kb),
	camera(_cam),
	cursor_ray(camera -> getPosition(), camera -> getDirection()),
	RSQ(scenemanager -> createRayQuery(cursor_ray))
{}

OgrikFrameListener :: ~ OgrikFrameListener()
{
	scenemanager -> destroyQuery(RSQ);
}


