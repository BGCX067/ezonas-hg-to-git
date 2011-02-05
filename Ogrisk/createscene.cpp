#include "stdafx.h"

void Application :: createScene()
{
//camera -> setPolygonMode(PM_WIREFRAME);
	// the ogre
	
	// sinbad = scenemanager -> createEntity("Sinbad.mesh");
	// rootnode -> attachObject(sinbad);
	
// the plane
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane("plane", 
	ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane, 
	1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scenemanager -> createEntity("LightPlaneEntity", "plane");
	scenemanager -> getRootSceneNode() -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("Examples/Rocky");
	// billboard for the laser and its dot
	// first, trying to load the dot
	// Nodes["dot"] = scenemanager -> createSceneNode("dot");
	laserdot = scenemanager -> createSceneNode("dot");
	rootnode -> addChild(laserdot);
	laserdot -> attachObject (bbset);
	laserdot -> setScale(0.005f, 0.005f, 0.005f);

	//bbchain = scenemanager -> createBillboardChain("laserbeam");
}