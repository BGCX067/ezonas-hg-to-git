#ifndef __APPLE__
#include "stdafx.h"
#endif

class Cam3rdperson:
	public Ogre :: Singleton <Cam3rdperson>,
	public KeyListener,
	public MouseListener
{
public:
	bool update();//float);
    static Cam3rdperson * getSingletonPtr(void);
	static Cam3rdperson * Instantiate();

protected:
	Cam3rdperson();
	~ Cam3rdperson();
	SceneNode
		* cam_node,
		* cam_yaw,
		* cam_pitch;
		//* cam_roll;
	Camera * cam;
	bool stop;
	
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
