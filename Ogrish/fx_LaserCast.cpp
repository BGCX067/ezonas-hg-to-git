#include "stdafx.h"


LaserCast :: LaserCast():
cam(appli ->camera),
	ray_cam		(Ray(Vec3(0, 0, 0), Vec3(-1, -1, -1))),
	RSQ (appli ->scmgr -> createRayQuery(ray_cam)),
	n_root		(appli ->rootnode),
	n_laserbeam (appli ->rootnode -> createChildSceneNode("laser beam")),
	n_laserdot	(appli ->rootnode -> createChildSceneNode("laser dot")),
	camera		(appli ->camera -> getPosition()),
	bb_dot		(appli ->scmgr -> createBillboardSet("laser dot")),
	bboard		(bb_dot -> createBillboard(Ogre :: Vector3(0, 0, 0))),
	bb_beam		(appli ->scmgr -> createBillboardChain("laser beam")),
	
	laser_width		(appli -> GetFloat("laser_width")),
	timeSinceLastFrame		(appli -> timeSinceLastFrame)

	,previous_vertex_count(0)
	,previous_indice_count(0)
{
	n_laserbeam -> attachObject (bb_beam);
	n_laserdot -> attachObject (bb_dot);
	bb_dot -> setMaterialName("jokoon/laser_dot");
	bb_beam -> setMaterialName("jokoon/laser_beam");
	n_laserdot -> setScale(appli ->GetVect3("dotscale"));
	
	bb_beam -> setMaxChainElements(2);
	bb_beam -> addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, 100), laser_width, 0, ColourValue()));
	bb_beam -> addChainElement
		(0, BillboardChain::Element
			(Vec3(0, 0, 0), laser_width, 0, ColourValue()));

	bb_beam -> setUseTextureCoords(true);
	bb_beam -> setTextureCoordDirection(BillboardChain :: TCD_V);
}
void LaserCast :: update()
{
	if(execute())
	{
		n_laserdot -> setPosition(result);
		bb_beam -> updateChainElement
			(0, 0, BillboardChain :: Element
				(result, laser_width, 0, ColourValue()));
		bb_beam -> updateChainElement
			(0, 1, BillboardChain :: Element
			(appli ->camera -> getRealPosition() + Vec3(0,2,0), laser_width, 0, ColourValue()));

		// last_entity, current_entity;
		if (ent_check == last_entity);
		else
		{
			//static_cast<SceneNode*>(last_entity->getParentNode())->showBoundingBox(false);
			//static_cast<SceneNode*>(ent_check->getParentNode())->showBoundingBox(true);
			//last_entity = ent_check;
		}


	}
}
