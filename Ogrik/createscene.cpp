#include "stdafx.h"

void Application :: createScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	// the ogre

	//sinbad = scenemanager -> createEntity(game_rc -> GetValue("sinbad"));
	//rootnode -> attachObject(sinbad);

	Entity * ent1 = scenemanager -> createEntity(game_rc -> GetValue("ent1"));
	SceneNode * node = scenemanager -> createSceneNode("dada");
	rootnode -> addChild(node);
	ent1 -> setMaterialName("fourchanfaces");
	node -> attachObject(ent1);
	node -> setScale(0.05, 0.05, 0.05);

	//SceneNode * node = scenemanager -> createSceneNode("node");
// the plane
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane("plane",
	ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
	1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scenemanager -> createEntity("LightPlaneEntity", "plane");
	rootnode -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("Examples/Rocky");

// billboard for the laser and its dot
	laserdot = scenemanager -> createSceneNode("laserdot");
	rootnode -> addChild(laserdot);
// first, trying to load the dot
#define SET
#ifdef SET
//billboard SET
	bbset = scenemanager -> createBillboardSet("laser_dot");
	bboard = bbset -> createBillboard(Ogre :: Vector3(0, 0, 0));
	bbset -> setMaterialName("Ogrik/laser");
	laserdot -> attachObject (bbset);
#else
//billboard CHAIN
	bbchain = scenemanager -> createBillboardChain("laser_ray");
	laserdot -> attachObject (bbchain);
	bbchain -> addChainElement();
#endif
//
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
