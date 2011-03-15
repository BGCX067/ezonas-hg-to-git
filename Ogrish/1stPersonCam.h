#include "stdafx.h"

class FPersonCam
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	FPersonCam();
	~ FPersonCam();
	// void update(float, float, Vec3 &);
	bool update(float);
	static FPersonCam * sglt();
protected:
	SceneNode
		* cam_node,
		* cam_yaw,
		* cam_pitch;
		//* cam_roll;
	Camera * cam;
	
	// tweakables
	float moving_speed, rotating_speed;

	// gameplay objects
	LaserCast * lasercast;
	BulletTracer * bullet_tracer;

	// inputs
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
	
};
