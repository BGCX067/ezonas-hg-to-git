#include "stdafx.h"

BulletTracer :: BulletTracer (Camera * camera, SceneManager * scmagr):
	
	bullet_speed	(ConfMgr :: sglt() -> GetFloat("bullet_speed")),
	trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length")),
	scmgr			(scmagr),
	cam				(camera),
	nextbullet		(0), was_fired(false), time_stack (0),

	bb_bullet_model	(scmagr -> createBillboardChain("bullet trace"))
	//n_bullet		(scmgr -> getRootSceneNode() ->createChildSceneNode())
{
	bb_bullet_model -> setMaterialName("jokoon/bullet_trace");
	bb_bullet_model -> setTextureCoordDirection(BillboardChain :: TCD_V);
	bb_bullet_model -> setUseTextureCoords(true);
	bb_bullet_model -> setMaxChainElements(2);
	
	bb_bullet_model -> addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, 0), trace_width, 0, ColourValue()));

	bb_bullet_model -> addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, - trace_length), trace_width, 0, ColourValue()));

	//n_bullet -> attachObject (bb_bullet_model);
	FOR(BULLET_MAX)
	{
		bb_bullet[i] = new BillboardChain(* bb_bullet_model);
		n_bullet[i] = scmgr -> getRootSceneNode() ->createChildSceneNode();
		n_bullet[i] -> attachObject(bb_bullet[i]);
	}
}
BulletTracer :: ~ BulletTracer () {}
void BulletTracer :: Fire ()
{
	if (was_fired == false)
	{
		n_bullet[nextbullet] -> setPosition(cam -> getDerivedPosition() + Vec3(0, -1, -1));
		n_bullet[nextbullet] -> setOrientation(cam -> getDerivedOrientation());
		was_fired = true;
		(nextbullet += 1) %= BULLET_MAX;

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
		if (time_stack > 0.1f)
		{
			time_stack = 0.0f;
			was_fired = false;
		}
	}
}

	// classic
	//n_bullet -> setPosition(cam -> getPosition());
	//n_bullet -> setDirection(cam -> getDirection());
	// Real (world)
	//n_bullet -> setPosition(cam -> getRealPosition());
	//n_bullet -> setDirection(cam -> getRealDirection());
	// Derived