#include "stdafx.h"

void Application :: CreateScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
//	SceneNode * node;
	AddPlane();
	//scmgr -> showBoundingBoxes(true);
	//ConfMgr :: getSingletonPtr() -> AddLevel("guy"); 
	//ConfMgr :: getSingletonPtr() -> AddLevel("mifflin3"); 
	

	n_ball = SGLT_RSN -> createChildSceneNode("bally");
	e_ball = SGLT_SCMGR -> createEntity("geosphere4500.mesh");
	n_ball -> attachObject(e_ball);

	n_ball -> setScale(Vec3(0.003, 0.003, 0.003));
	ConfMgr :: getSingletonPtr() -> AddLight("light3");
	ConfMgr :: getSingletonPtr() -> AddLight("light4");
	gravity = Vec3 (0, -10, 0);
	cam_ctrlr -> setCamPosition(Vec3(0, 0, 10));
	ground_height = ConfMgr :: getSingleton() . GetFloat("ground_height");
	
}
void Application :: AddPlane()
{
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y,
		ConfMgr :: getSingleton() . GetFloat("plane_altitude"));
	float width_length = ConfMgr :: getSingleton() . GetFloat("plane_width_length");
	Ogre :: MeshManager :: getSingleton().createPlane
		("plane",
			ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
			width_length, width_length,
			20, 20,
			true,
			1, 5, 5,
			Ogre :: Vector3 :: UNIT_Z);

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