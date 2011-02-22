#include "stdafx.h"

class FPersonCam
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	FPersonCam(Camera * camera, SceneManager * scmgr);
	void update();
protected:
	SceneNode
		* cam_roll,
		* cam_yaw,
		* cam_pitch,
		* cam_node;
	Camera * cam;
};
