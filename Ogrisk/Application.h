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

private:
	static Application * instance;
	void createScene();
	Application();
	~ Application();
// core objects
	SceneManager * scenemanager;
	Root * root;
	RenderWindow * window;
	Camera * camera;
	Viewport * viewport;
// inputs
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
// game play
	GameConfig * gameconfig;
	const float moving_speed;
	const float rotating_speed;
// entities and nodes
	Entity * sinbad, * entplane;
	SceneNode * rootnode, * laserdot;
	//map <SceneNode *> Nodes;
// scene queries
	Ray cursor_ray;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	RSQR_iter_t rsqr_iter;
// Billboards
	Billboard * bboard;
	BillboardSet * bbset;
	BillboardChain * bbchain;
// Manual objects
    ManualObject * manobj;
};

