#include "stdafx.h"

Application * Application :: instance = NULL;

Application :: Application():
	FrameListener(),
	root(new Root("conf/plugins_d.cfg", "conf/Ogre.cfg"))
{
	// OGRE SPECIFIC CODE ///////////////////////////////
	if(!(root -> restoreConfig() || root -> showConfigDialog()))
		exit(0xdeadbeef);
	window = root -> initialise(true, "Ogre3D Beginners Guide");
	window -> reposition(20, 20);
	scmgr = root -> createSceneManager(ST_GENERIC);
	rootnode = scmgr -> getRootSceneNode();
	camera = scmgr -> createCamera("Camera");
	camera -> setNearClipDistance(1);
	viewport = window -> addViewport(camera);
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
	ovl_mgr = OverlayManager :: getSingletonPtr();
	ovl_crosshair = ovl_mgr -> getByName("jokoon/crosshair");

	ConfMgr :: Instantiate("conf/gameconf.cfg");
	fpersoncam = new FPersonCam(camera, rootnode, window);
	createScene();
}
Application :: ~ Application()
{
	delete fpersoncam;
	if(root) delete root;
}
void Application :: go ()
{
	root -> startRendering();
}
Application * Application :: sglt()
{
	static Application _;
	return & _;
}
SceneManager * Application :: GetScMgr()
{
	return scmgr;
}
