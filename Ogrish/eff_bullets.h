#include "stdafx.h"

struct bullet_raycast:
	public btCollisionWorld :: RayResultCallback
{
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
	{
		//m_collisionObject, m_localShapeInfo, m_hitNormalLocal, m_hitFraction
		static_cast<SceneNode*>
			(rayResult.m_collisionObject -> getUserPointer())
				-> showBoundingBox(true);
		return 0.0f;
	}
};

void meh()
{
	btCollisionWorld :: ClosestRayResultCallback crrc(btVector3(0,0,0),btVector3(0,0,0));
	crrc;
		//camera -> getRealPosition()

}

struct laser_raycast:
	public btCollisionWorld :: RayResultCallback
{
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult, bool normalInWorldSpace)
	{
		//m_collisionObject, m_localShapeInfo, m_hitNormalLocal, m_hitFraction
		static_cast<SceneNode*>
			(rayResult.m_collisionObject -> getUserPointer())
				-> showBoundingBox(true);
		return 0.0f;
	}
};
