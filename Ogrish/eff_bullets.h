#include "stdafx.h"

struct bullet_raycast:
	public btCollisionWorld :: RayResultCallback
{
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
	{
		//m_collisionObject, m_localShapeInfo, m_hitNormalLocal, m_hitFraction
		static_cast<SceneNode*>
			(rayResult.m_collisionObject -> getUserPointer())
				-> showBoundingBox(true);
		return 342.2f;
	}
};
