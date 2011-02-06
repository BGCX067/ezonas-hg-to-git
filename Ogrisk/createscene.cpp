#include "stdafx.h"

void Application :: createScene()
{
//camera -> setPolygonMode(PM_WIREFRAME);
	// the ogre

    sinbad = scenemanager -> createEntity("Sinbad.mesh");
    rootnode -> attachObject(sinbad);

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

//billboard SET
	bbset = scenemanager -> createBillboardSet("laser_dot");
	bboard = bbset -> createBillboard(Ogre :: Vector3(0, 0, 0));
	bbset -> setMaterialName("Ogrik/laser");
//billboard CHAIN

	bbchain = scenemanager -> createBillboardChain("laser_ray");
	bbchain -> addChainElement();

	laserdot = scenemanager -> createSceneNode("dot");
	rootnode -> addChild(laserdot);
	laserdot -> attachObject (bbset);
	laserdot -> attachObject (bbchain);
	laserdot -> setScale(0.005f, 0.005f, 0.005f);
    laserdot -> setPosition(10, 0, 0);



// the manual boject
	//	manobj = scenemanager -> createManualObject("duh");
	//	manobj -> begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
	//		manobj -> position (0, 0, 0);
	//		manobj -> colour(1, 0, 0, 0.1);
	//		manobj -> position (0, 1000, 0);
	//		manobj -> colour(1, 0, 0, 0.1);
	//	manobj -> end();
	//	laserdot -> attachObject (manobj);

}
