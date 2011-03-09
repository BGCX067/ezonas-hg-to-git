#include "stdafx.h"

void Application :: CreateScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	SceneNode * node;
	AddPlane();
	//QuickAdd("Sinbad.mesh");
	ConfMgr :: sglt() -> FastAdd("ninja");
	// the manual boject ///////////////////////////////////////////////////////////////
	//	manobj = scenemanager -> createManualObject("duh");
	//	manobj -> begin("BaseWhiteNoLighting", RenderOperation::OT_LINE_STRIP);
	//		manobj -> position (0, 0, 0);
	//		manobj -> colour(1, 0, 0, 0.1);
	//		manobj -> position (0, 1000, 0);
	//		manobj -> colour(1, 0, 0, 0.1);
	//	manobj -> end();
	//	laserdot -> attachObject (manobj);
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
	entplane -> setMaterialName("Examples/Rocky");
}
