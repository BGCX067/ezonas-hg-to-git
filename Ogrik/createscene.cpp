#include "stdafx.h"

void Application :: createScene()
{
// the ogre
	//camera -> setPolygonMode(PM_WIREFRAME);
	sinbad = scenemanager -> createEntity("Sinbad.mesh");
	scenemanager -> getRootSceneNode() -> attachObject(sinbad);
// the plane
	Ogre :: Plane plane(Ogre :: Vector3 :: UNIT_Y, -10);
	Ogre :: MeshManager :: getSingleton().createPlane("plane", 
	ResourceGroupManager :: DEFAULT_RESOURCE_GROUP_NAME, plane, 
	1500, 1500, 20, 20, true, 1, 5, 5, Ogre :: Vector3 :: UNIT_Z);

	entplane = scenemanager -> createEntity("LightPlaneEntity", "plane");
	scenemanager -> getRootSceneNode() -> createChildSceneNode() -> attachObject(entplane);
	entplane -> setMaterialName("Examples/Rocky");

	// ent -> setMaterialName("highlight");
}