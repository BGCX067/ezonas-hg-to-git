#include "stdafx.h"

class FPersonCam
{
public:
	// bool RaycastFromPoint(const Vector3 & point, const Vector3 & normal, Vector3 & result);
	FPersonCam(Camera * camera, SceneNode * rootscnd);
	void update(float, float, Vec3 &);
protected:
	SceneManager * scmgr;
	SceneNode
		* cam_node,
		* cam_yaw,
		* cam_pitch,
		* cam_roll;
	Camera * cam;

};
