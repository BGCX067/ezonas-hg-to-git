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
	gravity = Vec3 (0, - ConfMgr :: getSingleton() . GetFloat("gravity"), 0);
	velocity = Vec3 (0, 0, 0);
	vel_prev = Vec3 (0, 0, 0);
	pos_prev = Vec3 (0, 0, 0);
	acc_prev = Vec3 (0, 0, 0);
	position = Vec3 (0, ConfMgr :: getSingleton() . GetFloat("initial_height"), 0);
	cam_ctrlr -> GetNode() -> setPosition(0, 10, 10);
	cam_ctrlr -> GetNode() -> rotate(Vec3(1,0,0), Radian(Degree(-75)));	
}
void Application :: AddPlane()
{
	float width_length = ConfMgr :: getSingleton() . GetFloat("plane_width_length");
	float altitude = ConfMgr :: getSingleton() . GetFloat("plane_altitude");
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
		{
			Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, altitude);
			Ogre :: MeshManager :: getSingleton().createPlane
				("plane",
					ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
					width_length, width_length,
					1, 1,
					true,
					1,
					1, 1,
					Ogre :: Vector3 :: UNIT_Z);

			entplane = scmgr -> createEntity("LightPlaneEntity", "plane");
			rootnode -> createChildSceneNode() -> attachObject(entplane);
			entplane -> setMaterialName("jokoon/grass");
		}
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