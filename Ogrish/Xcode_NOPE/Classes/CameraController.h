#include "stdafx.h"

class CameraController:
	public Ogre :: Singleton <CameraController>,
	public KeyListener,
	public MouseListener
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	bool update();//float);
    static CameraController * getSingletonPtr(void);
	static CameraController * Instantiate();
	void setFollowedTarget(SceneNode * node);
	void setCameraMode(int mode);
	SceneNode * getTargetNode();
	SceneNode * getMasterNode();
	void setEntity(Entity * ent);
protected:
	SceneNode
		* n_root	,

		* n_master  ,	 // those 3 in this exact order
		* n_target	,	 // those 3 in this exact order
		* n_cam		,	 // those 3 in this exact order
		
		* n_yawpitch_ptr; // this node will serve as a pointer to switch between 1st/rd person cam

	Entity * character;
	float moving_speed, rotating_speed, * frame_time;
	Camera * cam;
	bool stop;
	Vec3 offset;
	int camera_mode;
	
	// gameplay objects
	LaserCast * lasercast;
	BulletTracer * bullet_tracer;

	// inputs
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
	Vec3 translate, translate2;

	/////////////// METHODS ///////////////
	CameraController();
	~ CameraController();
	bool mouseMoved(const OIS::MouseEvent &e);
	bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed(const OIS::KeyEvent &e);
	bool keyReleased(const OIS::KeyEvent &e);

};
