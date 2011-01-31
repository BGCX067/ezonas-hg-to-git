#include "stdafx.h"

class OgrikFrameListener;

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
// scene queries
	Ray cursor_ray;
	RaySceneQuery * RSQ;
};

