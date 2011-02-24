#include "stdafx.h"

class OgrikFrameListener;

typedef RaySceneQueryResult :: iterator RSQR_iter_t;

class Application: public FrameListener
{
public:
	// enum state_ctrl_mode {FPS, CURSOR} ctrl_mode;
	// void renderOneFrame();
	static Application * GetSingleton();//	{return instance;}
	static void Instantiate();// {static Application inst; instance = & inst;}
	void go();

// added those 3 lines
	bool frameRenderingQueued(const FrameEvent & evt);
	SceneNode * QuickAdd(string str);
	SceneNode * FastAdd(string str);
private:
	static Application * instance;
	const float GetFloat(string _s);
	void createScene();
	Application();
	~ Application();
	void AddPlane();
// core objects ###############################################################
	SceneManager * scenemanager;
	Root * root;
	RenderWindow * window;
	Camera * camera;
	Viewport * viewport;
// inputs #####################################################################
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
// game play ##################################################################
	ConfigFile * configfile;
	float moving_speed, rotating_speed;
	FPersonCam * fpersoncam;
// entities and nodes #########################################################
	Entity * sinbad, * entplane;
	SceneNode * rootnode, * laserdot, * laserbeam, * bullet_t;
	//map <SceneNode *> Nodes;
// scene queries ##############################################################
	RayCast * raycast;
	Vec3 laser_hit;
	float laser_width, bullet_speed, trace_width, trace_length;
// Billboards #################################################################
	Billboard * bboard;
	BillboardSet * bbset;
	BillboardChain * bbchain, * bullet_trace;
// Manual objects #############################################################
    //ManualObject * manobj;
};

