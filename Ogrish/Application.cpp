//#ifndef __APPLE__
#include "stdafx.h"
//#endif
template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

bool Application :: init_config()
{
	configfile = new ConfigFile;
#ifdef __APPLE__
	configfile -> load(macBundlePath() +
		"/Contents/Resources/"+"conf/gameconf.cfg");
#else
	configfile -> load("conf/gameconf.cfg");
#endif

	if(root -> restoreConfig()) return true;
	else
		if(root -> showConfigDialog()) return false;
	else
		exit (0xdeadbeef);
}

Application :: Application():
	FrameListener(),
#ifdef __APPLE__
root				(new Root(macBundlePath() + "/Contents/Resources/"+"conf/plugins_d-mac.cfg",
						  macBundlePath() + "/Contents/Resources/"+"conf/Ogre.cfg",
						  macBundlePath() + "/Contents/Resources/"+"conf/Ogre.log")),
#else
	root			(new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log")),
#endif	// this tricks was made to make sure all those objects are
	// initiallized at the creation of the application
	// (some speed up maybe...)
#ifndef CONSTR
	last_init		(init_config()),

	window			(root -> initialise(true, "Zevil")			),
	scmgr			(root -> createSceneManager(GetScMgrType())	),
	camera			(scmgr -> createCamera("Camera")			),
	viewport		(window -> addViewport(camera)				),
	rootnode		(scmgr -> getRootSceneNode()				),
	mGorilla		(new Gorilla :: Silverback()				),
	machine			(new game_machine)/*,
	hover_idle		(MaterialManager::getSingleton().getByName("hover/idle")),
	hover_hover		(MaterialManager::getSingleton().getByName("hover/hover"))*/
	

#ifdef PHYSICS
	,
	broadphase				(new btDbvtBroadphase()),
    collisionConfiguration	(new btDefaultCollisionConfiguration()),
    dispatcher				(new btCollisionDispatcher(collisionConfiguration)),
	//solver					(new btSequentialImpulseConstraintSolver),
    //dynamicsWorld			(new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration))
    collisionWorld			(new btCollisionWorld(dispatcher,broadphase,collisionConfiguration))

#endif
#endif
{
	window -> reposition(20, 20);
	camera -> setNearClipDistance(1);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);
	InitResources();

	// PROJECT CODE ////////////////////////////////////////
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	
	//switch(ConfMgr :: getSingleton().GetInt("camera_mode"))
	cam_ctrlr = CameraController :: Instantiate();
	
	// CreateTerrain();
	InitGorilla();

	CreateScene();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));
#ifdef PHYSICS
	btCollisionObject * colobj = new btCollisionObject;

	//collisionWorld->getCollisionObjectArray().resize(10, colobj);


	sphere = new btSphereShape(GetFloat("sphere_radius"));
	//	collisionWorld->addCollisionObject(new );

	//collisionWorld->addCollisionObject(new btSphereShape(3));
	//collisionWorld->addCollisionObject(new btSphereShape(3));
	//collisionWorld->addCollisionObject(new btSphereShape(3));
	//collisionWorld->addCollisionObject(new btSphereShape(3));
	//collisionWorld->getCollisionObjectArray()[0]->setWorldTransform(
#endif
	sphere_radius_squared = GetFloat("sphere_radius");
	sphere_radius_squared *= sphere_radius_squared;
}
Application :: ~ Application()
{

#ifdef USE_TERRAIN
	OGRE_DELETE mTerrain;
	OGRE_DELETE mGlobals;
#endif
	delete console;
	delete mGorilla;
	delete machine;
	// bullet
#ifdef PHYSICS
	int sz = collisionWorld->getCollisionObjectArray().size();
	for(size_t i = 0; i < sz; ++i)
		if(collisionWorld->getCollisionObjectArray()[i])
			delete collisionWorld->getCollisionObjectArray()[i];

	delete sphere;
	// delete dynamicsWorld;
	// delete solver;
    delete dispatcher;
    delete collisionConfiguration;
    delete broadphase;
#endif
	delete configfile;

	if(root) delete root;
	else exit(0xb00b);
}
void Application :: go ()
{
	root -> startRendering();
	//while(!stop) root ->renderOneFrame();
}

void Application :: moveTo(int idx, Vec3 dest, float speed)
{
	if(idx < Nodes.size())
	{
		isMoving[idx] = true;
		Vec3 direction (Nodes[idx]->getPosition() - dest);
		velocities[idx] = direction * speed / direction.length();
	}
}

SceneManager * Application :: GetScMgr()	{ return scmgr;						   }
SceneNode * Application :: GetRSN()			{ return scmgr -> getRootSceneNode();  }
Camera * Application :: GetCam()			{ return camera;					   }
RenderWindow * Application :: GetRW()		{ return window;					   }
float * Application :: GetFT()				{ return & frame_time;				   }
Ogre::ConfigFile * Application :: GetCFG()  { return configfile;				   }