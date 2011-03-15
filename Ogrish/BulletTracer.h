#include "stdafx.h"

#define BULLET_MAX 5

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
	float bullet_speed, trace_width, trace_length, time_stack;
	bool was_fired;
	Camera * cam;
	SceneNode * n_bullet[BULLET_MAX];
	BillboardChain * bb_bullet_model;
	BillboardChain * bb_bullet[BULLET_MAX];
};