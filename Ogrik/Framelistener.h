#include "stdafx.h"

class OgrikFrameListener : public FrameListener
{
public:
	OgrikFrameListener (SceneManager * _scmgr, Camera * _cam,
	InputManager * _inputmanager, Mouse * _mouse, Keyboard * _kb);
	~ OgrikFrameListener();
	bool frameRenderingQueued(const FrameEvent & evt);
	
private:
	SceneManager * scenemanager;
	
	InputManager * inputmanager;
	Keyboard * keyboard;
	Camera * camera;
	Mouse * mouse;

	Ray cursor_ray;
	RaySceneQuery * RSQ;
};

