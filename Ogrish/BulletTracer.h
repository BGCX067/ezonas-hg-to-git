#ifndef __APPLE__
#include "stdafx.h"
#endif

#define BULLET_MAX 5

class BulletTracer:
	public BillboardChainFactory,
	public Ogre :: Singleton <BulletTracer>
{
public:
	void Fire();
	void update();//float frame_time);
	//static BulletTracer * sglt();
    static BulletTracer * getSingletonPtr(void);
	static BulletTracer * Instantiate();
private:
	BulletTracer();
	~ BulletTracer();
	SceneManager * scmgr;
	int nextbullet, bullets_max;
	float bullet_speed,
		trace_width, trace_length,
		time_stack, fire_delay, * frame_time,
		offset_x, offset_y;
	bool was_fired;
	Camera * cam;
	SceneNode * n_bullet [BULLET_MAX];

	BillboardChain * bb_bullet_model;
	BillboardSet * bb_dot[BULLET_MAX];
	BillboardChain * bb_bullet[BULLET_MAX];
	SceneNode * n_cannon;
//	BulletFactory * bulletfactory;

	BillboardChain * MakeABullet(string);

};