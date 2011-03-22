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
	scmgr			(root -> createSceneManager(ST_GENERIC)),
	camera			(scmgr -> createCamera("Camera")),
	viewport		(window -> addViewport(camera)),
	rootnode		(scmgr -> getRootSceneNode()),

	mGorilla		(new Gorilla :: Silverback())
	
{
	// OGRE SPECIFIC CODE ///////////////////////////////
	//if(!(root -> restoreConfig() || root -> showConfigDialog()))
	//window = root -> initialise(true, "Ogre3D Beginners Guide");
	window -> reposition(20, 20);
	//scmgr = root -> createSceneManager(ST_GENERIC);
	//rootnode = scmgr -> getRootSceneNode();
	//camera = scmgr -> createCamera("Camera");
	camera -> setNearClipDistance(1);
	//viewport = window -> addViewport(camera);
	viewport -> setBackgroundColour(ColourValue(0.1, 0.1, 0.1));
	camera -> setAspectRatio
	(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);

	// RESOURCES ////////////////////////////////////////
    ConfigFile cf;
    cf.load("conf/resources_d.cfg");

    ConfigFile :: SectionIterator sectionIter = cf.getSectionIterator();
    String sectionName, typeName, dataname;
    while (sectionIter.hasMoreElements())
    {
        sectionName = sectionIter.peekNextKey();
        ConfigFile :: SettingsMultiMap * settings = sectionIter.getNext();
        ConfigFile :: SettingsMultiMap :: iterator i;
        for (i = settings -> begin(); i != settings -> end(); ++i)
        {
            typeName = i -> first;
            dataname = i -> second;
            ResourceGroupManager :: getSingleton().addResourceLocation(
				dataname, typeName, sectionName);
        }
	}
    ResourceGroupManager :: getSingleton().initialiseAllResourceGroups();
 	
	// PROJECT CODE ////////////////////////////////////////
	// overlays mgr
	ovl_mgr = OverlayManager :: getSingletonPtr();
	
	// some sort of crosshair
	ovl_mgr -> getByName("jokoon/crosshair") -> show();

	// some text
	//ovl_mgr -> getByName("jokoon/sometext")
	//	-> getChild("sometext")
	//	-> setCaption("Oh mon doudou !");
	//ovl_mgr -> getByName("jokoon/sometext") -> show();

	// project objects
	//ConfMgr :: Instantiate("conf/gameconf.cfg");
	ConfMgr :: Instantiate();

	//fpersoncam = FPersonCam :: getSingletonPtr();
	fpersoncam = FPersonCam :: Instantiate();

	// create the terrain
	// CreateTerrain();

	mGorilla -> loadAtlas("test");
	gor_screen = mGorilla -> createScreen(viewport, "test");
	gor_layer = gor_screen -> createLayer();//10,10, "", 15);

	gor_rect = gor_layer -> createRectangle(0, 0);
	gor_rect -> background_colour(ColourValue(0.3, 0.3, 0.3, 0.3));

	gor_caption = gor_layer -> createCaption(7, 2, 2, string("Counter Cake"));
	//gor_layer -> createMarkupText(7, 0, 0, string("Counter Cake"));

	//gor_layer -> setVisible(true);
	// create the scene
	CreateScene();
	camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

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
