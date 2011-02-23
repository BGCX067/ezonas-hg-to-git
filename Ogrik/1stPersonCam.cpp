#include "stdafx.h"

FPersonCam :: FPersonCam(Camera * camera, SceneNode * rootscnd):

	cam_node	(rootscnd->createChildSceneNode("cam_node")),
	cam_yaw		(cam_node->createChildSceneNode("cam_yaw")),
	cam_pitch	(cam_yaw->createChildSceneNode("cam_pitch")),
	cam_roll	(cam_pitch->createChildSceneNode("cam_roll")),
	cam			(camera)

{
	cam_roll -> 	attachObject(cam);
}

void FPersonCam :: update(float yaw, float pitch, Vec3 & vect)
{
	cam_yaw -> yaw(Radian(yaw));
	cam_pitch -> pitch(Radian(pitch));
//	cam_node -> translate(* vect);//, Node::TS_LOCAL);
	cam_node -> translate
		(
			cam_yaw -> getOrientation() *
			cam_pitch -> getOrientation() *
			vect
		);//, Node::TS_LOCAL);
}
