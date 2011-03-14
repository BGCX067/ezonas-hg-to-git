#include "stdafx.h"

class BulletTracer
{
public:
	BulletTracer(Camera * camera, SceneManager * scmgr);
	~ BulletTracer();
	void Fire();
	void update(float frame_time);
private:
	SceneManager * scmgr;
	int nextbullet;
	float bullet_speed, trace_width, trace_length;
	Camera * cam;
	SceneNode * n_bullet;//[BULLET_MAX];
	BillboardChain * bb_bullet_model;
	BillboardChain * bb_bullet[BULLET_MAX];

};