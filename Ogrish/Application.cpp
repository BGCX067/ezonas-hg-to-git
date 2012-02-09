//#ifndef __APPLE__
#include "stdafx.h"
//#endif
template<> Application * Ogre :: Singleton <Application> :: ms_Singleton = 0;

Application :: Application():
	FrameListener()
{
	configfile = new ConfigFile;

	/* initializing all objects */
#ifdef __APPLE__
	root			 = new Root(macBundlePath() + "/Contents/Resources/"+"conf/plugins_d-mac.cfg",
						macBundlePath() + "/Contents/Resources/"+"conf/Ogre.cfg",
						macBundlePath() + "/Contents/Resources/"+"conf/Ogre.log");
	configfile -> load(macBundlePath() + "/Contents/Resources/"+"conf/gameconf.cfg");
#else
	root			 = new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log");
	configfile -> load("conf/gameconf.cfg");
#endif
	if(root -> restoreConfig() == false)
		if (root -> showConfigDialog() == false)
			exit (0xdeadbeef);

	window			 = root -> initialise(true, "Zevil");
	scmgr			 = root -> createSceneManager(GetScMgrType());
	camera			 = scmgr -> createCamera("Camera");
	viewport		 = window -> addViewport(camera);
	rootnode		 = scmgr -> getRootSceneNode();
	
	InitResources(); // DONT FORGET THIS STEP

	cam_ctrlr		 = CameraController :: Instantiate();
	lasercast		 = LaserCast :: Instantiate();
	bullet_tracer	 = BulletTracer :: Instantiate();
	mGorilla		 = new Gorilla :: Silverback();
	machine			 = new game_machine;
	mat3_zero		 = btMatrix3x3(0,0,0,0,0,0,0,0,0);
	transf			 = btTransform(mat3_zero);
	hover_idle		 = MaterialManager::getSingleton().getByName("hover/idle");
	hover_hover		 = MaterialManager::getSingleton().getByName("hover/hover");

#ifdef PHYSICS
	broadphase				 = new btDbvtBroadphase();
    collisionConfiguration	 = new btDefaultCollisionConfiguration();
    dispatcher				 = new btCollisionDispatcher(collisionConfiguration);
	//solver				 = new btSequentialImpulseConstraintSolver;
    //dynamicsWorld			 = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    collisionWorld			 = new btCollisionWorld(dispatcher,broadphase,collisionConfiguration);
#endif

	/* changing some settings */
	window -> reposition(20, 20);
	camera -> setNearClipDistance(1);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	camera -> setAspectRatio
		(Real(viewport -> getActualWidth())/ Real(viewport -> getActualHeight()));
	root -> addFrameListener(this);
	InitResources();

	initialize();
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


SceneManager * Application :: GetScMgr()	{ return scmgr;						   }
SceneNode * Application :: GetRSN()			{ return scmgr -> getRootSceneNode();  }
Camera * Application :: GetCam()			{ return camera;					   }
RenderWindow * Application :: GetRW()		{ return window;					   }
float * Application :: GetFT()				{ return & frame_time;				   }
Ogre::ConfigFile * Application :: GetCFG()  { return configfile;				   }