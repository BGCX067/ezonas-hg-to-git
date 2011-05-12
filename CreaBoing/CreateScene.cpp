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
	position = Vec3 (0, ConfMgr :: getSingleton() . GetFloat("initial_height"), 0);
	cam_ctrlr -> GetNode() -> setPosition(0, 5, 5);
	cam_ctrlr -> GetNode() -> rotate(Vec3(1,0,0), Radian(Degree(-60)));	
}
void Application :: AddPlane()
{
	n_plane = rootnode -> createChildSceneNode();
	n_plane -> setPosition(-11, 0, -11);
	float width_length = ConfMgr :: getSingleton() . GetFloat("plane_width_length");
	float altitude = ConfMgr :: getSingleton() . GetFloat("plane_altitude");
	float grid_step = ConfMgr :: getSingleton() . GetFloat("grid_step");
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
		{
			Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, altitude);
			Ogre :: MeshManager :: getSingleton().createPlane
				("plane" + TO_STR(i) + "-" + TO_STR(j),
					ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
					width_length * grid_step, width_length * grid_step,
					// segments X, Y, NORMALS, numtexcoordset, uTile, vTile
					1, 1, true, 1, 1, 1,
					Ogre :: Vector3 :: UNIT_Z);

			entplane = scmgr -> createEntity
				("LightPlaneEntity"+ TO_STR(i) + "-" + TO_STR(j),
				"plane" + TO_STR(i) + "-" + TO_STR(j));
			
			nodes[i*10 + j] = n_plane -> createChildSceneNode();
			nodes[i*10 + j] -> attachObject(entplane);
			nodes[i*10 + j] -> setPosition(i * grid_step, 0, j * grid_step);
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