#include "stdafx.h"

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
#ifdef DEBUG
	root  = new Root("conf/plugins_d.cfg", "conf/Ogre.cfg", "conf/Ogre.log");
#else	 
	root  = new Root("conf/plugins.cfg", "conf/Ogre.cfg", "conf/Ogre.log");
#endif
	configfile -> load("conf/gameconf.cfg");
#endif
	if(root -> restoreConfig() == false)
		if (root -> showConfigDialog() == false)
			exit (0xdeadbeef);

	window	 = root -> initialise(true, "Zevil");
	scmgr	 = root -> createSceneManager(GetScMgrType());
	camera	 = scmgr -> createCamera("Camera");
	viewport = window -> addViewport(camera);
	rootnode = scmgr -> getRootSceneNode();
					   
	InitResources(); // DONT FORGET THIS STEP

	cam_ctrlr		= CameraController :: Instantiate();
	lasercast		= LaserCast		:: Instantiate();
	bullet_tracer	= BulletTracer		:: Instantiate();
	mGorilla		= new Gorilla		:: Silverback();
	machine			= new game_machine;
	mat3_zero		= btMatrix3x3(0,0,0,0,0,0,0,0,0);
	transf			= btTransform(mat3_zero);
	
	broadphase		 = new btDbvtBroadphase();
    collisionConfig	 = new btDefaultCollisionConfiguration();
    dispatcher		 = new btCollisionDispatcher(collisionConfig);
	//solver		 = new btSequentialImpulseConstraintSolver;
    //dynamicsWorld	 = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    collisionWorld	 = new btCollisionWorld(dispatcher,broadphase,collisionConfig);
	mesh2shape		 = new BtOgre::StaticMeshToShapeConverter;


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
