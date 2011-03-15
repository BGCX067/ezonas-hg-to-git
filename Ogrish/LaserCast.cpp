#include "stdafx.h"

LaserCast :: LaserCast():
	cam(SGLT_CAM),
	ray_cam		(Ray(Vec3(0, 0, 0), Vec3(-1, -1, -1))),
	//ray_cam (Ray(Vec3(0,0,0), Vec3(-1, -1, -1))),
	RSQ (SGLT_SCMGR -> createRayQuery(ray_cam)),
	// nodes
	n_root		(SGLT_RSN),
	n_laserbeam (SGLT_RSN -> createChildSceneNode("laser beam")),
	n_laserdot	(SGLT_RSN -> createChildSceneNode("laser dot")),
	//n_bullet	(scmgr -> createSceneNode("bullet trace")),
	
	// billboards
	bb_dot		(SGLT_SCMGR -> createBillboardSet("laser dot")),
	bboard		(bb_dot -> createBillboard(Ogre :: Vector3(0, 0, 0))),
	bb_beam		(SGLT_SCMGR -> createBillboardChain("laser beam")),
	//bb_bullet	(scmgr -> createBillboardChain("bullet trace")),
	
	laser_width		(ConfMgr :: sglt() -> GetFloat("laser_width"))
	//bullet_speed	(ConfMgr :: sglt() -> GetFloat("bullet_speed")),
	//trace_width		(ConfMgr :: sglt() -> GetFloat("trace_width")),
	//trace_length	(ConfMgr :: sglt() -> GetFloat("trace_length"))
{
	// "link" the laser dot position so that the class can update the position
	// child nodes
	//n_root -> addChild(n_laserbeam);
	//n_root -> addChild(n_laserdot);
	//n_root -> addChild(n_bullet);

	// attach objects
	n_laserbeam -> attachObject (bb_beam);
	n_laserdot -> attachObject (bb_dot);
	//n_bullet -> attachObject (bb_bullet);

	// materials
	bb_dot -> setMaterialName("jokoon/laser_dot");
	bb_beam -> setMaterialName("jokoon/laser_beam");
	//bb_bullet -> setMaterialName("jokoon/bullet_trace");
	
	n_laserdot -> setScale(0.005f, 0.005f, 0.005f);
	
	bb_beam -> setMaxChainElements(2);
	bb_beam -> addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, 100), laser_width, 0, ColourValue()));
	bb_beam->addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, 0), laser_width, 0, ColourValue()));

	bb_beam -> setUseTextureCoords(true);
	bb_beam -> setTextureCoordDirection(BillboardChain :: TCD_V);
	
	//bb_bullet -> setTextureCoordDirection(BillboardChain :: TCD_V);
	//bb_bullet -> setUseTextureCoords(true);
	//bb_bullet -> setMaxChainElements(2);
	//bb_bullet -> addChainElement
	//	(0, BillboardChain::Element
	//		(Vec3(0, 0, 0), trace_width, 0, ColourValue()));
	//bb_bullet->addChainElement
	//	(0, BillboardChain::Element
	//		(Vec3(trace_length, 0, 0), trace_width, 0, ColourValue()));
}
void LaserCast :: update(float frame_time)
{
	if(execute())
	{
		n_laserdot -> setPosition(result);
		bb_beam -> updateChainElement
			(0, 0, BillboardChain :: Element
				(result, laser_width, 0, ColourValue()));
	}
	//n_bullet -> translate(frame_time * bullet_speed, 0, 0);
}

LaserCast * LaserCast :: sglt()
{
	static LaserCast _;
	return & _;
}