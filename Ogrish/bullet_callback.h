#include "stdafx.h"

struct callback: public btCollisionWorld :: ContactResultCallback
{
	virtual	btScalar addSingleResult
		(btManifoldPoint& cp,
		const btCollisionObject* colObj0, int partId0, int index0,
		const btCollisionObject* colObj1, int partId1, int index1)
	{
		static_cast<SceneNode*>(colObj0->getUserPointer())->showBoundingBox(true);
		static_cast<SceneNode*>(colObj0->getUserPointer())->showBoundingBox(true);
	}
};