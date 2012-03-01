#include "stdafx.h"

BulletTracer :: BulletTracer ():
	
	bullet_speed	(appli -> GetFloat("bullet_speed")),
	trace_width		(appli -> GetFloat("trace_width")),
	trace_length	(appli -> GetFloat("trace_length")),
	cam				(appli -> camera),
	nextbullet		(0),
	was_fired		(false),
	time_stack		(0),
	fire_delay		(appli -> GetFloat("fire_delay")),
	timeSinceLastFrame		(appli -> timeSinceLastFrame),
	offset_x		(appli -> GetFloat("offset_x")),
	offset_y		(appli -> GetFloat("offset_y"))

{
	n_bullet		 .resize(BULLET_MAX);
	bb_dot			 .resize(BULLET_MAX);
	bb_bullet		 .resize(BULLET_MAX);
	raycast_callback .resize(BULLET_MAX);

	FOR(BULLET_MAX)
	{
		bb_bullet[i] = MakeABullet("bullet"+TO_STR(i));
		bb_dot[i] = appli ->scmgr -> createBillboardSet();
		bb_dot[i] -> createBillboard(Vec3(0,0,0));
		bb_dot[i] -> setMaterialName("jokoon/bullet_dot");
		Ogre::Vector2 v = appli ->GetVect2("bullet_dot");
		bb_dot[i]
			-> getMaterial() -> getTechnique(0u) -> getPass(0u)
			-> getTextureUnitState(0u) -> setTextureScale(v.x, v.y);
		n_bullet[i] = appli ->rootnode -> createChildSceneNode("bullet"+TO_STR(i));
		n_bullet[i] -> attachObject(bb_bullet[i]);
		n_bullet[i] -> attachObject(bb_dot[i]);
	}
}
BulletTracer :: ~ BulletTracer (){}
void BulletTracer :: Fire ()
{
	if (was_fired == false)
	{
		n_bullet[nextbullet] -> setPosition
			(cam -> getDerivedPosition() + Vec3(0, offset_x, offset_y));
		n_bullet[nextbullet] -> setOrientation(cam -> getDerivedOrientation());
		was_fired = true;

		nextbullet += 1;
		nextbullet %= BULLET_MAX;
	}
	
}
void BulletTracer :: update ()//float frame_time)
{
	FOR(BULLET_MAX)
		n_bullet[i] -> translate(0, 0, -  timeSinceLastFrame * bullet_speed, Ogre :: Node :: TS_LOCAL);
	
	// bullet raycast
	ray_start = cam->getDerivedPosition();
	ray_end = ray_start + cam->getDerivedDirection();

	arg_start = btVector3(ray_start.x, ray_start.y, ray_start.z);
	arg_end = btVector3(ray_end.x, ray_end.y, ray_end.z);
	// btCollisionWorld :: ClosestRayResultCallback RayCallback(arg_start, arg_end);
	// Perform raycast
 
	if(RayCallback.hasHit())
	{
		//End = RayCallback.m_hitPointWorld;
		//Normal = RayCallback.m_hitNormalWorld;
		// Do some clever stuff here
	}
	appli->collisionWorld->rayTest(arg_start, arg_end, callbacks[nextbullet]);


	if(was_fired == true)
	{
		time_stack += timeSinceLastFrame;
		if (time_stack > fire_delay)
		{
			time_stack = 0.0f;
			was_fired = false;
		}
	}
}
BillboardChain * BulletTracer :: MakeABullet(string str)
{
	// MovableObject*
	BillboardChain * result = (BillboardChain *) createInstance (str, appli ->scmgr);

	result -> setMaterialName("jokoon/bullet_trace");
	result -> setTextureCoordDirection(BillboardChain :: TCD_V);
	result -> setUseTextureCoords(true);
	result -> setMaxChainElements(2);

	result -> addChainElement (0, BillboardChain::Element
								(Vec3(0, 0, 0), trace_width, 0, ColourValue()));

	result -> addChainElement (0, BillboardChain::Element
								(Vec3(0, 0, trace_length), trace_width, 0, ColourValue()));

	return result;
}

