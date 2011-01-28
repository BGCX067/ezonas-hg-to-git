#include "stdafx.h"

class OgrikFrameListener : public FrameListener
{
public:
	OgrikFrameListener(RenderWindow* win,Camera* cam);
	~ OgrikFrameListener();
	bool frameStarted(const FrameEvent& evt);
	
private:
	InputManager* _InputManager;
	Keyboard* _Keyboard;
	Mouse* _Mouse;
	Camera* _Cam;
	float _movementspeed;
};

