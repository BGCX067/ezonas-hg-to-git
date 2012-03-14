#include "stdafx.h"

void Application :: setCameraMode	(int mode)
{
	/*
1. put a node (A) at the focus point you want to orbit around 			 # Target
2. make a child node (B) and set its position to (0,0, orbitdistance) 	 # cam
3. reset the orientation & position of the camera 						 #
4. attach the camera to node B 											 # cam
5. optionally setFixedYaw on node A 									 #
6. to orbit, yaw and pitch node A based on the x/y of the mouse 		 #
	// root master target yaw pitch cam	
	*/	// root master target yaw pitch cam	
	/* 
	default arch:
	root --> master --> target --> cam 
	yaw_pitch_ptr = target
	*/
	if(mode == camera_mode) return;

	n_master -> detachAllObjects();		n_master -> removeAllChildren();
	n_target -> detachAllObjects();		n_target -> removeAllChildren();
	n_cam	 -> detachAllObjects();		n_cam	 -> removeAllChildren();
	n_recoil -> detachAllObjects();	    n_recoil -> removeAllChildren();
	camera_mode = mode;

	REINIT (n_cam)
	REINIT (n_master)
	REINIT (camera)
	REINIT (n_target)
	REINIT (n_recoil)
	switch (mode)
	{
	case 1:
		/////////////////////
		n_master -> addChild(n_cam);
		n_cam -> addChild(n_recoil);
		n_master -> addChild(n_target); /////// MEH

		n_recoil	 -> attachObject(camera);
		/////////////////////
		n_target->setFixedYawAxis(false);
		n_yawpitch_ptr = n_cam;
		break;

	case 3:
		/////////////////////
		n_master -> addChild(n_target);
		n_target -> addChild(n_cam);

		n_target -> attachObject(e_target);
		n_cam->setPosition(0,0,10);
		n_cam->attachObject(camera);
		/////////////////////
		n_target->setFixedYawAxis(true);
		n_yawpitch_ptr = n_target;
		break;
	default:
		exit(0xb00b);
		break;
	}
}
