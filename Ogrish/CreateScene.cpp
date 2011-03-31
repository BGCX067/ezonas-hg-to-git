#include "stdafx.h"

void Application :: CreateScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
//	SceneNode * node;
	AddPlane();
	
	//SceneNode * node = Application :: GetRSN() -> createChildSceneNode("patinous");
	//Entity * ent = Application :: GetScMgr() -> createEntity("patinous.mesh");
	//ent -> setMaterialName("patinous");
	
	//SceneNode * node = Application :: GetRSN() -> createChildSceneNode("dust11");
	//Entity * ent = Application :: GetScMgr() -> createEntity("dust1-rest.mesh");
	//ent -> setMaterialName("dust11");

	//node -> attachObject(ent);
	
	//(Entity *) (no -> getAttachedObject("patinous"));
	//ent -> 
	// NO NINJA NO MO'E
	//ConfMgr :: getSingletonPtr() -> FastAdd("dust1"); // NO NINJA NO MO'E
	//ConfMgr :: getSingletonPtr() -> FastAdd("m9");
	//ConfMgr :: getSingletonPtr() -> FastAdd("mtar"); 
	//ConfMgr :: getSingletonPtr() -> FastAdd("psg1"); 
	//ConfMgr :: getSingletonPtr() -> FastAdd("m416"); 
	ConfMgr :: getSingletonPtr() -> FastAdd("mifflin"); 
	
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