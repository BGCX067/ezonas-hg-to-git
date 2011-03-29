#include "stdafx.h"

class FPersonCam:
	public Ogre :: Singleton <FPersonCam>,
	public KeyListener,
	public MouseListener
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	bool update();//float);
	//static FPersonCam * sglt();
    static FPersonCam * getSingletonPtr(void);
	static FPersonCam * Instantiate();

protected:
	FPersonCam();
	~ FPersonCam();
	SceneNode
		* cam_node,
		* cam_yaw,
		* cam_pitch;
		//* cam_roll;
	Camera * cam;
	bool _continue;
	
	// tweakables
	float moving_speed, rotating_speed, * frame_time;

	// gameplay objects
	LaserCast * lasercast;
	BulletTracer * bullet_tracer;

	// inputs
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;

	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

	Vec3 translate;
};