#include "stdafx.h"

class OgrikFrameListener;

typedef RaySceneQueryResult :: iterator RSQR_iter_t;

class Application: public FrameListener
{
public:
	// enum state_ctrl_mode {FPS, CURSOR} ctrl_mode;
	// void renderOneFrame();
	static Application * GetSingleton()	{return instance;}
	static void Instantiate() {static Application inst; instance = & inst;}
	void go();

// added those 3 lines
	bool frameRenderingQueued(const FrameEvent & evt);
	SceneNode * QuickAdd(string str);
private:
	static Application * instance;
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
	GameConfig * gameconfig;
	GameResource * game_rc;
	const float moving_speed;
	const float rotating_speed;
// entities and nodes #########################################################
	Entity * sinbad, * entplane;
	SceneNode * rootnode, * laserdot, * laserbeam, * bullet_t;
	//map <SceneNode *> Nodes;
// scene queries ##############################################################
	RayCast * raycast;
	Vec3 laser_hit;
	const float laser_width;
// Billboards #################################################################
	Billboard * bboard;
	BillboardSet * bbset;
	BillboardChain * bbchain, * bullet_trace;
// Manual objects #############################################################
    //ManualObject * manobj;
};

