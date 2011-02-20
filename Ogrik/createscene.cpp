#include "stdafx.h"

SceneNode * Application :: QuickAdd(string str)
{
	SceneNode * node = scenemanager -> createSceneNode();
	node -> attachObject(scenemanager -> createEntity(str));
	rootnode -> addChild(node);
	return node;
}
void Application :: createScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	AddPlane();
	SceneNode * node;
	QuickAdd("Sinbad.mesh");// -> showBoundingBox(true);"ninja.mesh"
	node = QuickAdd("ninja.mesh");// -> setMaterialName("fourchanfaces");

	{// billboard for the laser dot
		laserdot = scenemanager -> createSceneNode("laser dot");
		// "link" the laser dot position so that the class can update the position
		raycast -> SetPos(& laser_hit);
		rootnode -> addChild(laserdot);
		bbset = scenemanager -> createBillboardSet("laser dot");
		bboard = bbset -> createBillboard(Ogre :: Vector3(0, 0, 0));
		bbset -> setMaterialName("Ogrik/laser_dot");
		laserdot -> attachObject (bbset);
		laserdot -> setScale(0.005f, 0.005f, 0.005f);
	}
	{//billboard CHAIN, for the laser beam
		laserbeam = scenemanager -> createSceneNode("laser beam");
		rootnode -> addChild(laserbeam);
		bbchain = scenemanager -> createBillboardChain("laser beam");
		laserbeam -> attachObject (bbchain);

		BillboardChain::Element head(Vec3(0, 10, 0), laser_width, 0, ColourValue(0, 0, 1));
		BillboardChain::Element tail(Vec3(0, 0, 10), laser_width, 0, ColourValue(1, 0, 0));
		bbchain -> setMaxChainElements(2);

		bbchain->addChainElement(0, head);
		bbchain->addChainElement(0, tail);
		// bbchain->addChainElement(0, BillboardChain::Element());
		// bbchain->addChainElement(1, BillboardChain::Element());
		
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
