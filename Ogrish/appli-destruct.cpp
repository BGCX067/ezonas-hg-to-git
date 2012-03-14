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

	 inputmanager -> destroyInputObject( mouse);
	 inputmanager -> destroyInputObject( keyboard);
	OIS::InputManager :: destroyInputSystem( inputmanager);

	// bullet
	size_t sz = colw->getCollisionObjectArray().size();
	for(size_t i = 0; i < sz; ++i)
		if(colw->getCollisionObjectArray()[i])
			delete colw->getCollisionObjectArray()[i];

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
