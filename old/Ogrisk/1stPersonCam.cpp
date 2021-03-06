#include "stdafx.h"

FPersonCam :: FPersonCam(Camera * camera, SceneManager * scmagr):

	scmgr		(scmagr),
	cam			(camera),
	cam_roll	(scmgr->createSceneNode("cam_roll")),
	cam_yaw		(scmgr->createSceneNode("cam_yaw")),
	cam_pitch	(scmgr->createSceneNode("cam_pitch")),
	cam_node	(scmgr->createSceneNode("cam_node"))

{
	scmgr -> getRootSceneNode() ->
					addChild(cam_node);
	cam_node ->		addChild(cam_yaw);
	cam_yaw ->		addChild(cam_pitch);
	cam_pitch ->	addChild(cam_roll);
	cam_roll -> 	addChild(cam_yaw);

	cam_roll -> 	attachObject(cam);
}

void FPersonCam :: update(float yaw, float pitch)
{
	cam_yaw -> yaw(Radian(yaw));
	cam_pitch -> pitch(Radian(pitch));
}
