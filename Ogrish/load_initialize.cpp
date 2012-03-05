#include "stdafx.h"

void Application :: init_engines()
{
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("                     INITIALIZING OGRE3D;                        ");
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("-------- loading resources.cfg --------");
	InitResources();

	PRINTLOG("------- bullet objects -------");
	broadphase		= new btDbvtBroadphase();
    collisionConfig	= new btDefaultCollisionConfiguration();
    dispatcher		= new btCollisionDispatcher(collisionConfig);
	//solver		= new btSequentialImpulseConstraintSolver;
    //dynamicsWorld	= new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    collisionWorld	= new btCollisionWorld(dispatcher,broadphase,collisionConfig);
	mesh2shape		= new BtOgre :: StaticMeshToShapeConverter;

	PRINTLOG("-------- camera controller, effects, GUI, gameplay --------");
	mGorilla		= new Gorilla	:: Silverback();
	machine			= new game_machine;
	
	n_master		= n_root   -> createChildSceneNode("master");
	n_target		= n_master -> createChildSceneNode("target");
	n_cam			= n_target -> createChildSceneNode("cam");
	n_yawpitch_ptr	= n_target;

	LoadEntity("bonome");
	init_bullet();
	init_bullets();
	translate = Vec3 (0.0f,0.0f,0.0f);
	translate2 = Vec3(0.0f,0.0f,0.0f);
	rotating_speed	=  GetFloat ("rotating_speed");
	moving_speed	=  GetFloat ("moving_speed");
	stop			= false;
	offset			= GetVect3("offset");
	rot				= 0.0f;
	mat3_zero		= btMatrix3x3(0,0,0,0,0,0,0,0,0);
	transf			= btTransform(mat3_zero);
}
void Application :: init_scene()
{

// ----- various options -----
	window -> reposition(20, 20);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();
	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	PRINTLOG("------- initializing GUI -------");
	InitGorilla();
	
// ----- scene creation -----
	PRINTLOG("------- creating the scene -------");
	if(GetString("loadlevel") == "yes")
	scmgr->getRootSceneNode()->createChildSceneNode()
		->attachObject(scmgr->createEntity(GetString("level")));

	AddPlane();
	setCameraMode(3);
	material_hover = create_hover_material
		(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
	if (configfile->getSetting("Populate") == "yes")
		Populate();
	if(GetString("enable_loadlist") == "yes")
		loadlist();

	AddLight("light3");
	AddLight("light3b");

	
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("        FINISHED INITIALIZING OGRE3D; begginning gameloop        ");
	PRINTLOG("-----------------------------------------------------------------");
}

