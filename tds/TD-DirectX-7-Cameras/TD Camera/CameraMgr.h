#include "stdafx.h"
#pragma once

class CameraMgr
{
public:
	CameraMgr();
	~ CameraMgr();
	void HandleKeys();
	void CycleCams();
	Camera * GetCamera(); // {return current_cam;}
private:	
	CameraDebug * cam_debug;
	CameraFPS * cam_fps;
	Camera * current_cam;
	
};