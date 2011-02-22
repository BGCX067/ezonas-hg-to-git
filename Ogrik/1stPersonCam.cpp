#include "stdafx.h"

FPersonCam :: FPersonCam(Camera * camera, SceneManager * scmgr):

	cam_roll	(new SceneNode),
	cam_yaw		(new SceneNode),
	cam_pitch	(new SceneNode),
	cam_node	(new SceneNode),
	scmgr		(scmgr),
	cam			(camera)

{}