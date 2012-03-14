#include "stdafx.h"
void Application :: update_laser()
{
	// setting ray to camera orientation
	from = camera -> getRealPosition() + camera ->getRealDirection(); // from
	//n_gizmo[0]->setPosition(temp);

	btfrom = BtOgre::Convert::toBullet(from);
	btto = BtOgre::Convert::toBullet(from + camera -> getRealDirection() * 50.0f);

	raycallback = btCollisionWorld::ClosestRayResultCallback (btfrom,btto);
	//raycallback.m_rayFromWorld = btVector3(temp.x,temp.x,temp.x);
	//raycallback.m_rayToWorld = btVector3(temp1.x,temp1.y,temp1.z);
	colw -> rayTest (btfrom, btto, raycallback);
	
	if(raycallback.hasHit())
	{
		btfrom = raycallback.m_hitPointWorld;
		n_laserdot -> setPosition(BtOgre::Convert::toOgre(btfrom));
		//LOGSTREAM<< "JUST HIT";
	
	bb_beam -> updateChainElement
		(0, 0, BillboardChain :: Element
			(BtOgre::Convert::toOgre(btfrom), laser_width, 0, ColourValue()));
	bb_beam -> updateChainElement
		(0, 1, BillboardChain :: Element
		(camera -> getRealPosition() + Vec3(0,2,0), laser_width, 0, ColourValue()));
	}
	//last_entity, current_entity;
	//if (ent_check == last_entity);
	//else
	//{
	//	//static_cast<SceneNode*>(last_entity->getParentNode())->showBoundingBox(false);
	//	//static_cast<SceneNode*>(ent_check->getParentNode())->showBoundingBox(true);
	//	//last_entity = ent_check;
	//}
}
