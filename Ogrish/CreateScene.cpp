#include "stdafx.h"

void Application :: CreateScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
//	SceneNode * node;
	AddPlane();
	scmgr -> showBoundingBoxes(true);	//ConfMgr :: getSingletonPtr() -> AddLevel("guy"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("dust1-1"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("dust1-2"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("dust1-3"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("dust2-1"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("M1A1"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("dust2-2"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("mifflin"); 
	
	ConfMgr :: getSingletonPtr() -> AddLight("light3");
	ConfMgr :: getSingletonPtr() -> AddLight("light4");
}
void Application :: AddPlane()
{
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane
		("plane",
			ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
			1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scmgr -> createEntity("LightPlaneEntity", "plane");
	rootnode -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("jokoon/grass");
}
void Application :: InitResources()
{
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
}