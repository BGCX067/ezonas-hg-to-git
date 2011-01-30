#include "stdafx.h"

void Application :: createScene()
{
	camera -> setPolygonMode(PM_WIREFRAME);
	Entity * ent = scenemanager -> createEntity("Sinbad.mesh");
	scenemanager -> getRootSceneNode() -> attachObject(ent);

	// ent -> setMaterialName("highlight");
}