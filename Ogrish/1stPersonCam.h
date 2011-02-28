#include "stdafx.h"

class FPersonCam
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	FPersonCam(Camera * camera, SceneNode * rootscnd, RenderWindow * _window);
	~ FPersonCam();
	// void update(float, float, Vec3 &);
	bool update(float);
protected:
	SceneManager * scmgr;
	SceneNode
		* cam_node,
		* cam_yaw,
		* cam_pitch,
		* cam_roll;
	Camera * cam;
	
	// tweakables
	float moving_speed, rotating_speed;

	// gameplay objects
	LaserCast * lasercast;
	
	// inputs
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
	
};
