#include "stdafx.h"

void Application :: createScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	
	{// the ogre and other ents
		sinbad = scenemanager -> createEntity(game_rc -> GetValue("sinbad"));
		SceneNode * sinbadnode = scenemanager -> createSceneNode("sinbad");
		sinbadnode -> attachObject(sinbad);
		rootnode -> addChild(sinbadnode);
		sinbadnode -> setPosition(5, 0, 0);
	}
	/*/ some sphere
		Entity * ent1 = scenemanager -> createEntity(game_rc -> GetValue("ent1"));
		SceneNode * node = scenemanager -> createSceneNode("dada");
		rootnode -> addChild(node);
		ent1 -> setMaterialName("fourchanfaces");
		node -> attachObject(ent1);
		node -> setScale(0.05, 0.05, 0.05);	
	//*/
	{// the plane
		Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
		Ogre :: MeshManager :: getSingleton().createPlane("plane",
		ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane,
		1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

		entplane = scenemanager -> createEntity("LightPlaneEntity", "plane");
		rootnode -> createChildSceneNode() -> attachObject(entplane);
		entplane -> setMaterialName("Examples/Rocky");
	}
	{// billboard for the laser and its dot
		laserdot = scenemanager -> createSceneNode("laser dot");
		raypick -> SetNode(laserdot);
		rootnode -> addChild(laserdot);
		bbset = scenemanager -> createBillboardSet("laser dot");
		bboard = bbset -> createBillboard(Ogre :: Vector3(0, 0, 0));
		bbset -> setMaterialName("Ogrik/laser_dot");
		laserdot -> attachObject (bbset);
		laserdot -> setScale(0.005f, 0.005f, 0.005f);
		laserdot -> setPosition(10, 0, 0);
		laserdot -> showBoundingBox();
	}
	{//billboard CHAIN, for the laser beam
		// laserbeam = scenemanager -> createSceneNode("laser beam");
		// rootnode -> addChild(laserbeam);
		// bbchain = scenemanager -> createBillboardChain("laser beam");
		// laserbeam -> attachObject (bbchain);
		// bbchain -> setMaterialName("Ogrik/laser_beam");

		// BillboardChain::Element head(Vec3(0, 10, 0), 0, 0, ColourValue(0, 0, 1));
		// BillboardChain::Element tail(Vec3(0, 0, 10), 0, 0, ColourValue(0, 0, 1));


		 // bbchain->addChainElement(0, head);
		 // bbchain->addChainElement(1, tail);
		//bbchain->addChainElement(0, BillboardChain::Element());
		//bbchain->addChainElement(1, BillboardChain::Element());
		
	}
	{// the manual boject
		//	manobj = scenemanager -> createManualObject("duh");
		//	manobj -> begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
		//		manobj -> position (0, 0, 0);
		//		manobj -> colour(1, 0, 0, 0.1);
		//		manobj -> position (0, 1000, 0);
		//		manobj -> colour(1, 0, 0, 0.1);
		//	manobj -> end();
		//	laserdot -> attachObject (manobj);
	}
}
