//#ifndef __APPLE__
#include "stdafx.h"
//#endif
void Application :: CreateScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
//	SceneNode * node;
	AddPlane();
	//scmgr -> showBoundingBoxes(true);
	//ConfMgr :: getSingletonPtr() -> AddLevel("guy"); 
	
	//ConfMgr :: getSingletonPtr() -> AddLevel("mifflin3");

	LoadEntity("bonome");

	//LoadEntity("dummy1");
	//LoadEntity("dummy2");
	//LoadEntity("dummy3");

	Populate();

	//cam_ctrlr -> getMasterNode()->attachObject(SGLT_SCMGR ->getEntity("bonome"));
	// cam_ctrlr -> getTargetNode() -> attachObject(SGLT_SCMGR -> getEntity("bonome"));

	//cam_ctrlr -> setTarget(SGLT_SCMGR -> getSceneNode("bonome"));

	AddLight("light1");
	AddLight("light2");

	Nodes.push_back(SGLT_SCMGR->getSceneNode("master"));
	int sz = Nodes.size();
	for (int i = 0; i < sz; ++ i)
	{
		PRINTLOG(Nodes[i]->getName());
	}
}
void Application :: AddPlane()
{
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -1); // -1 is the y position

	float plane_width = GetFloat("plane_width");
	float plane_depth = GetFloat("plane_depth");


	Ogre :: MeshManager :: getSingleton().createPlane
		("plane",
			ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
			plane_width, plane_depth, 10, 10, // width height xseg yseg
			true,
			1, 5, 5,
			//Vec3(1,1,4));
			Ogre :: Vector3 :: UNIT_Z);

	entplane = scmgr -> createEntity("LightPlaneEntity", "plane");
	rootnode -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("jokoon/grass");
}
void Application :: InitResources()
{
	// RESOURCES ////////////////////////////////////////
    ConfigFile cf;
#ifdef __APPLE__
    cf.load(macBundlePath() + "/Contents/Resources/"+"conf/resources_d.cfg");
	PRINTLOG(macBundlePath() + "/Contents/Resources/");
#else
    cf.load("conf/resources_d.cfg");
#endif

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
#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE || OGRE_PLATFORM == OGRE_PLATFORM_IPHONE
			Ogre::String archName;
            // OS X does not set the working directory relative to the app,
            // In order to make things portable on OS X we need to provide
            // the loading with it's own bundle path location
            if (!Ogre::StringUtil::startsWith(dataname, "/", false)) // only adjust relative dirs
                dataname = Ogre::String(Ogre::macBundlePath() + "/Contents/Resources/" + dataname);
#endif
            ResourceGroupManager :: getSingleton().addResourceLocation(
				dataname, typeName, sectionName);
        }
	}
    ResourceGroupManager :: getSingleton().initialiseAllResourceGroups();
}