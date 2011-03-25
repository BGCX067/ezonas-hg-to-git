#include "stdafx.h"

template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

bool Application :: init_config()
{
	if(root -> restoreConfig())
		return true;
	else
	if(root -> showConfigDialog())
		return false;
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
	//scmgr			(root -> createo(ST_)),
	scmgr			(root -> createSceneManager(ST_GENERIC)),
	camera			(scmgr -> createCamera("Camera")),
	viewport		(window -> addViewport(camera)),
	rootnode		(scmgr -> getRootSceneNode()),

	mGorilla		(new Gorilla :: Silverback())
	
{
	window -> reposition(20, 20);
	camera -> setNearClipDistance(1);
	viewport -> setBackgroundColour(ColourValue(0.1, 0.1, 0.1));
	camera -> setAspectRatio
	(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);

	root ->loadPlugin("");

	InitResources();

	// PROJECT CODE ////////////////////////////////////////
	// overlays mgr
	ovl_mgr = OverlayManager :: getSingletonPtr();
	
	// some sort of crosshair
	ovl_mgr -> getByName("jokoon/crosshair") -> show();
	ConfMgr :: Instantiate();
	fpersoncam = FPersonCam :: Instantiate();

	// CreateTerrain();

	InitGorilla();

	// create the scene
	CreateScene();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));
}
Application :: ~ Application()
{
	//delete fpersoncam;
#ifdef USE_TERRAIN
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
#endif
	if(root) delete root;
	else exit(0xb00b);
}
void Application :: go ()
{
	root -> startRendering();
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
