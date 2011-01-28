#include "stdafx.h"

class OgrikFrameListener;

class Application
{
private:

	SceneManager * _sceneManager;
	
	Root * _root;
	
	OgrikFrameListener * _listener;
	
	bool _keepRunning;
public:

	Application();
	~Application();
	void loadResources();
	int startup();
	void createScene();
	void renderOneFrame();
	bool keepRunning();
};

