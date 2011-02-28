#include "stdafx.h"

void Application :: createScene()
{
	//camera -> setPolygonMode(PM_WIREFRAME);
	SceneNode * node;
	{// plane and entities ////////////////////////////////////////////////////////////
		AddPlane();
		//QuickAdd("Sinbad.mesh");
		node = ConfMgr :: sglt() -> FastAdd("ninja");
	}
	{// the manual boject ///////////////////////////////////////////////////////////////
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
