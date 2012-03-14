#include "stdafx.h"
void Application :: init_laser()
{
	//ray_cam		 = Ray(Vec3(0, 0, 0), Vec3(-1, -1, -1));
	//RSQ			 = scmgr -> createRayQuery(ray_cam);

	// laser DOT
	n_laserdot	 = n_root -> createChildSceneNode("laser dot");
	bb_laserdot	 = scmgr  -> createBillboardSet("laser dot");
	n_laserdot -> attachObject (bb_laserdot);
	bb_laserdot -> setMaterialName("jokoon/laser_dot");
	float laserdot_scale = GetFloat("dotscale");
	n_laserdot -> setScale(Vec3(laserdot_scale,laserdot_scale,laserdot_scale));
	bboard		 = bb_laserdot -> createBillboard(Ogre :: Vector3(0, 0, 0));

	// laser BEAM
	laser_width = GetFloat("laser_width");
	n_laserbeam  = n_root -> createChildSceneNode("laser beam");
	bb_beam		 = scmgr  -> createBillboardChain("laser beam");
	n_laserbeam -> attachObject (bb_beam);
	bb_beam -> setMaterialName("jokoon/laser_beam");
	bb_beam -> setMaxChainElements(2);
	bb_beam -> addChainElement (0, BillboardChain::Element
		(Vec3(0, 0, 100), laser_width, 0, ColourValue()));
	bb_beam -> addChainElement (0, BillboardChain::Element
		(Vec3(0, 0, 0), laser_width, 0, ColourValue()));
	bb_beam -> setUseTextureCoords(true);
	bb_beam -> setTextureCoordDirection(BillboardChain :: TCD_V);
}

