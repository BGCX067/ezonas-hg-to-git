#include "stdafx.h"
//#define FOR(I) for(int i = 0; i < I; ++i)

BulletTracer :: BulletTracer (Camera * camera, SceneManager * scmgr):
	
	bullet_speed	(ConfMgr :: sglt() -> GetFloat("bullet_speed")),
	trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length")),
	cam				(camera),
	nextbullet(0)
{
	for(int i = 0; i < 30; ++i)
	{
		n_bullet[i] = scmgr -> createSceneNode();//"bullet trace");
		bb_bullet[i] = scmgr -> createBillboardChain();//"bullet trace");
		n_bullet[i] -> attachObject (bb_bullet[i]);

		bb_bullet[i] -> setMaterialName("jokoon/bullet_trace");
		
		bb_bullet[i] -> setTextureCoordDirection(BillboardChain :: TCD_V);
		bb_bullet[i] -> setUseTextureCoords(true);
		bb_bullet[i] -> setMaxChainElements(2);

		bb_bullet[i] -> addChainElement
			(0, BillboardChain::Element
				(Vec3(0, 0, 0), trace_width, 0, ColourValue()));

		bb_bullet[i] ->addChainElement
			(0, BillboardChain::Element
				(Vec3(trace_length, 0, 0), trace_width, 0, ColourValue()));
		
	}
}
BulletTracer :: ~ BulletTracer ()
{

}
void BulletTracer :: Fire ()
{
	n_bullet[nextbullet] -> setPosition(cam -> getDerivedPosition());
	n_bullet[nextbullet] -> setDirection(cam -> getDerivedDirection());
	(nextbullet += 1) %= 30;
}
void BulletTracer :: update (float frame_time)
{
	for(int i = 0; i < 30; ++i)
	{
		n_bullet[i] -> translate(frame_time * bullet_speed, 0, 0);
	}
}


