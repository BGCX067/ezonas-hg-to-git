#include "stdafx.h"

Application :: ~ Application()
{

#ifdef USE_TERRAIN
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
#endif
	delete console;
	delete mGorilla;
	delete machine;

	delete cam_ctrlr	 ;
	delete lasercast	 ;
	delete bullet_tracer ;

	// bullet
	size_t sz = collisionWorld->getCollisionObjectArray().size();
	for(size_t i = 0; i < sz; ++i)
		if(collisionWorld->getCollisionObjectArray()[i])
			delete collisionWorld->getCollisionObjectArray()[i];

	delete sphere;
	delete mesh2shape;
	// delete dynamicsWorld;
	// delete solver;
    delete dispatcher;
    delete collisionConfig;
    delete broadphase;
	delete configfile;

	if(root) delete root;
	else exit(0xb00b);
}
