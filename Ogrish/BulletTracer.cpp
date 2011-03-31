#include "stdafx.h"

template<> BulletTracer * Ogre :: Singleton <BulletTracer> :: ms_Singleton = 0;

BulletTracer :: BulletTracer ():
	
	bullet_speed	(ConfMgr :: getSingletonPtr() -> GetFloat("bullet_speed")),
	trace_width		(ConfMgr :: getSingletonPtr() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: getSingletonPtr() -> GetFloat("trace_length")),
	cam				(Application :: getSingletonPtr() -> GetCam()),
	// bb_bullet_model	(Application :: sglt() -> GetScMgr() -> createBillboardChain("bullet trace")),
	n_cannon		(Application :: getSingletonPtr() -> GetRSN() -> createChildSceneNode()),
	nextbullet		(0),
	was_fired		(false),
	time_stack		(0),
	fire_delay		(ConfMgr :: getSingletonPtr() -> GetFloat("fire_delay")),
	frame_time		(Application :: getSingletonPtr() -> GetFT()),
	offset_x		(ConfMgr :: getSingletonPtr() -> GetFloat("offset_x")),
	offset_y		(ConfMgr :: getSingletonPtr() -> GetFloat("offset_y"))

{
	char str[2];

	FOR(BULLET_MAX)
	{
		sprintf(str,"%d",i);
		bb_bullet[i] = MakeABullet(string(str));
		bb_dot[i] = SGLT_SCMGR -> createBillboardSet();
		bb_dot[i] -> createBillboard(Vec3(0,0,0));
		bb_dot[i] -> setMaterialName("jokoon/bullet_dot");
		n_bullet[i] = SGLT_RSN -> createChildSceneNode(string(str));
		n_bullet[i] -> attachObject(bb_bullet[i]);
		n_bullet[i] -> attachObject(bb_dot[i]);
	}
}
BulletTracer :: ~ BulletTracer ()
{
	//FOR(BULLET_MAX)
	//{
	//	if (bb_bullet[i]) //delete bb_bullet[i];
	//		//bulletfactory -> 
	//		destroyInstance(bb_bullet[i]);
	//}	
}
void BulletTracer :: Fire ()
{
	if (was_fired == false)
	{
		n_bullet[nextbullet] -> setPosition(cam -> getDerivedPosition()
			+ Vec3(0,
			offset_x,
			offset_y));
		n_bullet[nextbullet] -> setOrientation(cam -> getDerivedOrientation());
		was_fired = true;
		nextbullet += 1;
		nextbullet %= BULLET_MAX;
	}
}
void BulletTracer :: update ()//float frame_time)
{
	//for(int i = 0; i < bullets_max; ++i)
	//n_bullet -> translate(0, 0, -frame_time * bullet_speed, Ogre :: Node :: TS_LOCAL);
	FOR(BULLET_MAX)
	{
		n_bullet[i] -> translate(0, 0, - * frame_time * bullet_speed, Ogre :: Node :: TS_LOCAL);
	}
	if(was_fired == true)
	{
		time_stack += * frame_time;
		if (time_stack > fire_delay)
		{
			time_stack = 0.0f;
			was_fired = false;
		}
	}
}
//BulletTracer * BulletTracer :: sglt()
//{
//	static BulletTracer _;
//	return & _;
//}
BillboardChain * BulletTracer :: MakeABullet(string str)
{
	// MovableObject*
	BillboardChain * result = (BillboardChain *) createInstance (str, SGLT_SCMGR);

	result -> setMaterialName("jokoon/bullet_trace");
	result -> setTextureCoordDirection(BillboardChain :: TCD_V);
	result -> setUseTextureCoords(true);
	result -> setMaxChainElements(2);

	result -> addChainElement (0, BillboardChain::Element
								(Vec3(0, 0, 0), trace_width, 0, ColourValue()));

	result -> addChainElement (0, BillboardChain::Element
								(Vec3(0, 0, trace_length), trace_width, 0, ColourValue()));

	return result;
}

