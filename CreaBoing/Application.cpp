#include "stdafx.h"

template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

bool Application :: init_config()
{
	if(root -> restoreConfig()) return true;
	else
		if(root -> showConfigDialog()) return false;
	else
		exit (0xdeadbeef);
}
Application :: Application():
	FrameListener(),
	root			(new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log")),
	// this tricks was made to make sure all those objects are
	// initiallized at the creation of the application
	// (some speed up maybe...)
	last_init		(init_config()),

	window			(root -> initialise(true, "Zevil")),
	scmgr			(root -> createSceneManager(ConfMgr :: getSingletonPtr() -> GetScMgrType())),
	camera			(scmgr -> createCamera("Camera")),
	viewport		(window -> addViewport(camera)),
	rootnode		(scmgr -> getRootSceneNode()),

	mGorilla		(new Gorilla :: Silverback()),

	velocity (Vec3 (0, 0, 0)),
	vel_prev (Vec3 (0, 0, 0)),
	pos_prev (Vec3 (0, 0, 0)),
	acc_prev (Vec3 (0, 0, 0)),
	impact (Vec3 (0, 0, 0)),
	forces (Vec3 (0, 0, 0))

{
	window -> reposition(20, 20);
	camera -> setNearClipDistance(1);
	viewport -> setBackgroundColour(ColourValue(0.1, 0.1, 0.1));
	camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);
	InitResources();

	// PROJECT CODE ////////////////////////////////////////
	// overlays mgr
	ovl_mgr = OverlayManager :: getSingletonPtr();
	
	// some sort of crosshair
	ovl_mgr -> getByName("jokoon/crosshair") -> show();
	//ConfMgr :: Instantiate();
	//switch(ConfMgr :: getSingleton().GetInt("camera_mode"))
	cam_ctrlr = CameraController :: Instantiate();
	
	InitGorilla();
	velocity = Vec3(0,0,0);
	CreateScene();
	camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));
}
Application :: ~ Application()
{

#ifdef USE_TERRAIN
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
#endif
	delete mGorilla;
	// bullet
#ifdef PHYSICS
	delete dynamicsWorld;
    delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
#endif

	if(root) delete root;
	else exit(0xb00b);
}
void Application :: go ()					{ root -> startRendering(); }
Vec3 * Application :: GetVelocityAddress()  { return & velocity; }
SceneManager * Application :: GetScMgr()	{ return scmgr; }
SceneNode * Application :: GetRSN()			{ return scmgr -> getRootSceneNode(); }
Camera * Application :: GetCam()			{ return camera; }
RenderWindow * Application :: GetRW()		{ return window; }
float * Application :: GetFT()				{ return & frame_time; }