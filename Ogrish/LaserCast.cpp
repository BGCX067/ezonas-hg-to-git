#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
template<> LaserCast * Ogre :: Singleton <LaserCast> :: ms_Singleton = 0;

LaserCast :: LaserCast():
	cam(SGLT_CAM),
	ray_cam		(Ray(Ogre::Vector3(0, 0, 0), Ogre::Vector3(-1, -1, -1))),
	RSQ (SGLT_SCMGR -> createRayQuery(ray_cam)),
	n_root		(SGLT_RSN),
	n_laserbeam (SGLT_RSN -> createChildSceneNode("laser beam")),
	n_laserdot	(SGLT_RSN -> createChildSceneNode("laser dot")),
	camera(SGLT_CAM -> getPosition()),
	bb_dot		(SGLT_SCMGR -> createBillboardSet("laser dot")),
	bboard		(bb_dot -> createBillboard(Ogre :: Vector3(0, 0, 0))),
	bb_beam		(SGLT_SCMGR -> createBillboardChain("laser beam")),
	
	laser_width		(Application :: getSingletonPtr() -> GetFloat("laser_width")),
	frame_time		(Application :: getSingletonPtr() -> GetFT())
#ifdef OPTIM
	,previous_vertex_count(0)
	,previous_indice_count(0)
#endif
{
	n_laserbeam -> attachObject (bb_beam);
	n_laserdot -> attachObject (bb_dot);
	bb_dot -> setMaterialName("jokoon/laser_dot");
	bb_beam -> setMaterialName("jokoon/laser_beam");
	n_laserdot -> setScale(SGLT_APP->GetVect3("dotscale"));
	
	bb_beam -> setMaxChainElements(2);
	bb_beam -> addChainElement
		(0, Ogre::BillboardChain::Element
			(Ogre::Vector3(0, 0, 100), laser_width, 0, Ogre::ColourValue()));
	bb_beam -> addChainElement
		(0, Ogre::BillboardChain::Element
			(Ogre::Vector3(0, 0, 0), laser_width, 0, Ogre::ColourValue()));

	bb_beam -> setUseTextureCoords(true);
	bb_beam -> setTextureCoordDirection(Ogre::BillboardChain :: TCD_V);

	}
void LaserCast :: update()
{
	if(execute())
	{
		n_laserdot -> setPosition(result);
		bb_beam -> updateChainElement
			(0, 0, Ogre::BillboardChain :: Element
				(result, laser_width, 0, Ogre::ColourValue()));
		bb_beam -> updateChainElement
			(0, 1, Ogre::BillboardChain :: Element
			(SGLT_CAM -> getRealPosition() + Ogre::Vector3(0,2,0), laser_width, 0, Ogre::ColourValue()));
	}
}
#endif