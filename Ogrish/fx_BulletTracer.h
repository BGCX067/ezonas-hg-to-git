#include "stdafx.h"
struct bullet_raycast:
	public btCollisionWorld :: RayResultCallback
{
	virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace)
	{
		//	btCollisionObject * m_collisionObject
		//	LocalShapeInfo * 	m_localShapeInfo
		//	btVector3 			m_hitNormalLocal
		//	btScalar 			m_hitFraction

		static_cast<SceneNode*>
			(rayResult.m_collisionObject -> getUserPointer())
				-> showBoundingBox(true);
		return 342.2f;
	}
};
struct BulletTracer:
	public BillboardChainFactory
{
public:
	void Fire();
	void update();//float frame_time);
	BulletTracer();
	~ BulletTracer();
private:
	BillboardChain * MakeABullet(string);
	SceneManager * scmgr;
	ushort nextbullet;
	float bullet_speed,
		trace_width, trace_length,
		time_stack, fire_delay, & timeSinceLastFrame,
		offset_x, offset_y;
	Vec3 ray_start, ray_end;
	btVector3 arg_start, arg_end;

	bool was_fired;
	Camera * cam;
	BillboardChain * bb_bullet_model;
//#ifdef USE_ARRAYS
//	SceneNode * n_bullet [BULLET_MAX];
//	BillboardSet * bb_dot[BULLET_MAX];
//	BillboardChain * bb_bullet[BULLET_MAX];
//	btCollisionWorld :: ClosestRayResultCallback raycast_callback[BULLET_MAX];
//#endif
	std::vector<SceneNode *		>	n_bullet	;
	std::vector<BillboardSet *	>	bb_dot		;
	std::vector<BillboardChain *>	bb_bullet	;
	std::vector<bullet_raycast>		callbacks;
};