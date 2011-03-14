#include "stdafx.h"

class BulletTracer
{
public:
	BulletTracer(Camera * camera, SceneManager * scmgr);
	~ BulletTracer();
	void Fire();
	void update(float frame_time);
private:
	int nextbullet;
	Camera * cam;
	SceneNode * n_bullet[30];
	BillboardChain * bb_bullet[30];
	float bullet_speed, trace_width, trace_length;
};