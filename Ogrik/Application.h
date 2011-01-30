#include "stdafx.h"

class OgrikFrameListener;

class Application
{
public:
	// enum state_ctrl_mode {FPS, CURSOR} ctrl_mode;
	// void renderOneFrame();
	static Application * GetSingleton()	{return instance;}
	static void Instantiate() {static Application inst; instance = & inst;}
	void go();
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
// frame listener
	OgrikFrameListener * listener;
// game play	

// scene queries
};

