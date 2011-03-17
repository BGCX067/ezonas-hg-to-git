#include "stdafx.h"

#define BULLET_MAX 5

class BulletFactory;

class BulletTracer//: public BillboardChainFactory
{
public:
	void Fire();
	void update(float frame_time);
	static BulletTracer * sglt();
private:
	BulletTracer();
	~ BulletTracer();
	SceneManager * scmgr;
	int nextbullet;
	float bullet_speed, trace_width, trace_length, time_stack;
	bool was_fired;
	Camera * cam;
	SceneNode * n_bullet [BULLET_MAX];
	BillboardChain * bb_bullet_model;
	BillboardChain * bb_bullet[BULLET_MAX];
	SceneNode * n_cannon;
	BulletFactory * bulletfactory;
};

class BulletFactory: public BillboardChainFactory
{
	//protected:
	//	MovableObject* createInstanceImpl(const String& name, const NameValuePairList* params);
	float trace_width, trace_length;
	
public:
	BulletFactory();
	~BulletFactory();
	BillboardChain * MakeABullet(string);
	
	//const String& getType(void) const;
	//void destroyInstance( MovableObject* obj);
};