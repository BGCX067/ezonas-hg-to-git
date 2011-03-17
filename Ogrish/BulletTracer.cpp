#include "stdafx.h"

BulletTracer :: BulletTracer ():
	
	bullet_speed	(ConfMgr :: sglt() -> GetFloat("bullet_speed")),
	trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length")),
	cam				(Application :: sglt() -> GetCam()),
	// bb_bullet_model	(Application :: sglt() -> GetScMgr() -> createBillboardChain("bullet trace")),
	n_cannon		(Application :: sglt() -> GetRSN() -> createChildSceneNode()),
	nextbullet (0),
	was_fired(false),
	time_stack(0),
	bulletfactory(new BulletFactory)
{
	//bb_bullet_model -> setMaterialName("jokoon/bullet_trace");
	//bb_bullet_model -> setTextureCoordDirection(BillboardChain :: TCD_V);
	//bb_bullet_model -> setUseTextureCoords(true);
	//bb_bullet_model -> setMaxChainElements(2);
	//
	//bb_bullet_model -> addChainElement
	//	(0, BillboardChain::Element
	//		(Vec3(0, 0, 0), trace_width, 0, ColourValue()));

	//bb_bullet_model -> addChainElement
	//	(0, BillboardChain::Element
	//		(Vec3(0, 0, - trace_length), trace_width, 0, ColourValue()));

	////n_bullet -> attachObject (bb_bullet_model);
	//char str[10];
	//FOR(BULLET_MAX)
	//{
	//	sprintf(str,"%d",i);
	//	bb_bullet[i] = new BillboardChain(str/** bb_bullet_model*/);
	//	n_bullet[i] = Application :: sglt() -> GetRSN() -> createChildSceneNode();
	//	n_bullet[i] -> attachObject(bb_bullet[i]);
	//}

		char str[2];

	FOR(BULLET_MAX)
	{
		sprintf(str,"%d",i);
		bb_bullet[i] = bulletfactory -> MakeABullet(string(str));
		n_bullet[i] = SGLT_RSN -> createChildSceneNode(string(str));
		n_bullet[i] -> attachObject(bb_bullet[i]);
	}
}
BulletTracer :: ~ BulletTracer ()
{
	delete bulletfactory;
}
void BulletTracer :: Fire ()
{
	if (was_fired == false)
	{
		n_bullet[nextbullet] -> setPosition(cam -> getDerivedPosition() + Vec3(0, -0.3f, -0.3f));
		n_bullet[nextbullet] -> setOrientation(cam -> getDerivedOrientation());
		was_fired = true;
		nextbullet += 1;
		nextbullet %= BULLET_MAX;

	}
}
void BulletTracer :: update (float frame_time)
{
	//for(int i = 0; i < bullets_max; ++i)
	//n_bullet -> translate(0, 0, -frame_time * bullet_speed, Ogre :: Node :: TS_LOCAL);
	FOR(BULLET_MAX)
	{
		n_bullet[i] -> translate(0, 0, - frame_time * bullet_speed, Ogre :: Node :: TS_LOCAL);
	}
	if(was_fired == true)
	{
		time_stack += frame_time;
		if (time_stack > 0.5f)
		{
			time_stack = 0.0f;
			was_fired = false;
		}
	}
}
BulletTracer * BulletTracer :: sglt()
{
	static BulletTracer _;
	return & _;
}
BillboardChain * BulletFactory :: MakeABullet(string str)
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
								(Vec3(0, 0, - trace_length), trace_width, 0, ColourValue()));

	return result;
}
BulletFactory :: BulletFactory():
	trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length"))
{}
BulletFactory :: ~ BulletFactory()
{
		FOR(BULLET_MAX)
	{
		if (bb_bullet[i]) //delete bb_bullet[i];
			//bulletfactory -> 
			destroyInstance(bb_bullet[i]);
	}
}

