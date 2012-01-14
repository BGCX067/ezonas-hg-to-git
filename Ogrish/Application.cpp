#ifndef __APPLE__
#include "stdafx.h"
#endif

template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

bool Application :: init_config()
{
	configfile = new ConfigFile;
#ifdef __APPLE__
	configfile -> load(macBundlePath() +
		"/Contents/Resources/"+"conf/gameconf.cfg");
#else
	configfile -> load("conf/gameconf.cfg");
#endif

	if(root -> restoreConfig()) return true;
	else
		if(root -> showConfigDialog()) return false;
	else
		exit (0xdeadbeef);
}

Application :: Application():
	FrameListener(),
#ifdef __APPLE__
root			(new Root(macBundlePath() + "/Contents/Resources/"+"conf/plugins_d-mac.cfg",
						  macBundlePath() + "/Contents/Resources/"+"conf/Ogre.cfg",
						  macBundlePath() + "/Contents/Resources/"+"conf/Ogre.log")),
#else
root			(new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log")),
#endif	// this tricks was made to make sure all those objects are
	// initiallized at the creation of the application
	// (some speed up maybe...)
	last_init		(init_config()),

	window			(root -> initialise(true, "Zevil")),
	scmgr			(root -> createSceneManager(GetScMgrType())),
	camera			(scmgr -> createCamera("Camera")),
	viewport		(window -> addViewport(camera)),
	rootnode		(scmgr -> getRootSceneNode()),

	mGorilla		(new Gorilla :: Silverback()),
	game_machine	(new Game_machine)
	

#ifdef PHYSICS
	,
	broadphase				(new btDbvtBroadphase()),
    collisionConfiguration	(new btDefaultCollisionConfiguration()),
    dispatcher				(new btCollisionDispatcher(collisionConfiguration)),
    solver					(new btSequentialImpulseConstraintSolver),
    dynamicsWorld			(new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration))
#endif
{
	window -> reposition(20, 20);
	camera -> setNearClipDistance(1);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);
	InitResources();

	// PROJECT CODE ////////////////////////////////////////
	ovl_mgr = OverlayManager :: getSingletonPtr();
	//ovl_mgr -> getByName("jokoon/crosshair") -> show();
	
	//switch(ConfMgr :: getSingleton().GetInt("camera_mode"))
	cam_ctrlr = CameraController :: Instantiate();
	
	// CreateTerrain();
	InitGorilla();
	CreateScene();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

#ifdef PHYSICS
	dynamicsWorld->setGravity(btVector3(0,-10,0));
	
#endif
}
Application :: ~ Application()
{

#ifdef USE_TERRAIN
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
#endif
	delete mGorilla;
	delete game_machine;
	// bullet
#ifdef PHYSICS
	delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
#endif
	delete configfile;

	if(root) delete root;
	else exit(0xb00b);
}
void Application :: go ()
{
	root -> startRendering();
	//while(!stop) root ->renderOneFrame();
}
/*Application * Application :: sglt()
{
	static Application _;
	return & _;
}*/
SceneManager * Application :: GetScMgr()	{ return scmgr; }
SceneNode * Application :: GetRSN()			{ return scmgr -> getRootSceneNode(); }
Camera * Application :: GetCam()			{ return camera; }
RenderWindow * Application :: GetRW()		{ return window; }
float * Application :: GetFT()				{ return & frame_time; }
Ogre::ConfigFile * Application :: GetCFG()  { return configfile; }