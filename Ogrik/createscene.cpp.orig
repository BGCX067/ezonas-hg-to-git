#include "stdafx.h"

SceneNode * Application :: QuickAdd(string str)
{
	SceneNode * node = scenemanager -> createSceneNode(str);
	node -> attachObject(scenemanager -> createEntity(str));
	rootnode -> addChild(node);
	return node;
}
void Application :: createScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	{
		AddPlane();
		SceneNode * node;
		//QuickAdd("Sinbad.mesh");
		node = QuickAdd("ninja.mesh");
		node -> setScale(0.05f, 0.05f, 0.05f);
		((Entity *)(node -> getAttachedObject(0))) -> setMaterialName("Examples/Ninja");
		node -> translate(0, -5, 0);
	}
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
		bbchain -> setMaxChainElements(2);
		bbchain -> setMaterialName("Ogrik/laser_beam");
		bbchain->addChainElement
			(0, BillboardChain::Element(Vec3(0, 0, 100), laser_width, 0, ColourValue()));
		bbchain->addChainElement
			(0, BillboardChain::Element(Vec3(0, 0, 0), laser_width, 0, ColourValue()));

		bbchain -> setUseTextureCoords(true);
		//bbchain -> setUseVertexColours(true);
		bbchain -> setTextureCoordDirection(BillboardChain :: TCD_V);
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
