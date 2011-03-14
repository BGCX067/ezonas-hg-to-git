#include "stdafx.h"

BulletTracer :: BulletTracer (Camera * camera, SceneManager * scmagr):
	
	bullet_speed	(ConfMgr :: sglt() -> GetFloat("bullet_speed")),
	trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length")),
	scmgr			(scmagr),
	cam				(camera),
	nextbullet		(0),
	bb_bullet_model	(scmagr -> createBillboardChain()),
	n_bullet		(scmgr -> createSceneNode())
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
			(Vec3(trace_length, 0, 0), trace_width, 0, ColourValue()));


	//FOR(BULLET_MAX)
	//{
	//	n_bullet[i] = scmgr -> createSceneNode();//"bullet trace");
	//	//bb_bullet[i] = ;//"bullet trace");
	n_bullet -> attachObject (bb_bullet_model);
	//n_bullet -> setPosition(cam -> getDerivedPosition());
	//n_bullet -> setDirection(cam -> getDerivedDirection());
	n_bullet -> setPosition(cam -> getPosition());
	n_bullet -> setDirection(cam -> getDirection());
}
BulletTracer :: ~ BulletTracer () {}
void BulletTracer :: Fire ()
{
	//n_bullet -> setPosition(cam -> getDerivedPosition());
	//n_bullet -> setDirection(cam -> getDerivedDirection());
	n_bullet -> setPosition(cam -> getRealPosition());
	n_bullet -> setDirection(cam -> getRealDirection());
}
void BulletTracer :: update (float frame_time)
{
	//for(int i = 0; i < bullets_max; ++i)
	n_bullet -> translate(frame_time * bullet_speed, 0, 0);//, Ogre :: Node :: TS_LOCAL);
}


