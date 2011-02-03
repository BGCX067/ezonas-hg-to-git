#include "stdafx.h"

CameraMgr :: CameraMgr():
	cam_debug(new CameraDebug),
	cam_fps(new CameraFPS)
{}

CameraMgr :: ~ CameraMgr()
{
	delete cam_debug;
	delete cam_fps;
}

void CameraMgr :: HandleKeys()
{
#ifdef AZERTY
		if( :: GetAsyncKeyState('Z') & 0x8000f) current_cam -> walk(1.0f);
		if( :: GetAsyncKeyState('Q') & 0x8000f) current_cam -> strafe(-1.0f);
		if( :: GetAsyncKeyState('N') & 0x8000f) current_cam -> roll(0.1f);
		if( :: GetAsyncKeyState('M') & 0x8000f) current_cam -> roll(-0.1f);
#else
		if( :: GetAsyncKeyState('W') & 0x8000f) current_cam -> walk(1.0f);
		if( :: GetAsyncKeyState('A') & 0x8000f) current_cam -> strafe(-1.0f);
		if( :: GetAsyncKeyState('Q') & 0x8000f) current_cam -> roll(0.1f);
		if( :: GetAsyncKeyState('E') & 0x8000f) current_cam -> roll(-0.1f);
		if( :: GetAsyncKeyState('M') & 0x8000f) CycleCams();
		
#endif
		if( :: GetAsyncKeyState('S') & 0x8000f) current_cam -> walk(-1.0f);
		if( :: GetAsyncKeyState('D') & 0x8000f) current_cam -> strafe(1.0f);
		if( :: GetAsyncKeyState('R') & 0x8000f) current_cam -> fly(1.0f);
		if( :: GetAsyncKeyState('F') & 0x8000f) current_cam -> fly(-1.0f);
		if( :: GetAsyncKeyState(VK_UP) & 0x8000f) current_cam -> pitch(0.1f);
		if( :: GetAsyncKeyState(VK_DOWN) & 0x8000f) current_cam -> pitch(-0.1f);
		if( :: GetAsyncKeyState(VK_LEFT) & 0x8000f) current_cam -> yaw(-0.1f);
		if( :: GetAsyncKeyState(VK_RIGHT) & 0x8000f) current_cam -> yaw(0.1f);
}

void CameraMgr :: CycleCams()
{
	if(current_cam == cam_fps)
		current_cam = cam_debug;
		
	if(current_cam == cam_debug)
		current_cam = cam_fps;
}

Camera * CameraMgr :: GetCamera()
{
	return current_cam;
}