#include "stdafx.h"

void Application :: add_col_obj(size_t index)
{
	assert(index < Nodes.size());

	btCollisionObject * colobj = new btCollisionObject;
	colobj->setCollisionShape(sphere);
//	temp = Nodes[index] -> getPosition();
	colobj -> getWorldTransform().setOrigin(BtOgre::Convert::toBullet(Nodes[index] -> _getDerivedPosition()));
	colobj -> setUserPointer(Nodes[index]);
	colw -> addCollisionObject(colobj);
	hasCollided.push_back(false);
}
void Application :: init()
{
	LOGMSG("-----------------------------------------------------------------");
	LOGMSG("                     INITIALIZING OGRE3D;                        ");
	LOGMSG("-----------------------------------------------------------------");
	LOGMSG("-------- loading resources.cfg --------");
	init_resources();

	LOGMSG("------- allocating bullet objects -------");
	broadphase		= new btDbvtBroadphase();
    collisionConfig	= new btDefaultCollisionConfiguration();
    dispatcher		= new btCollisionDispatcher(collisionConfig);
	//solver		= new btSequentialImpulseConstraintSolver;
    //dynamicsWorld	= new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    colw			= new btCollisionWorld(dispatcher,broadphase,collisionConfig);
	mesh2shape		= new BtOgre :: StaticMeshToShapeConverter;

	LOGMSG("-------- allocating GUI, gameplay --------");
	mGorilla		= new Gorilla	:: Silverback();
	machine			= new game_machine;
#ifdef LASERCAST
	lasercast		= new LaserCast;
#endif
	// warning: some object's initialization depends on other, so *keep* this order
	// this is only required for core object, like camera node and character colobj
	// this is also required to populate objects before placing their colobj
	LOGMSG("------- creating the scene -------");
	if (GetString("loadlevel")		 == "yes") loadlevel("level");
	if (GetString("Populate")		 == "yes") Populate();
	if (GetString("enable_loadlist") == "yes") loadlist();
	AddLight("light3");
	AddLight("light3b");
	AddPlane();
	LoadEntity("bonome");
	LOGMSG("-------- creating camera scenenode tree and set camera mode --------");
	n_master = n_root   -> createChildSceneNode("master");
	n_target = n_master -> createChildSceneNode("target");
	n_cam	 = n_target -> createChildSceneNode("cam");
	n_recoil = scmgr    -> createSceneNode("recoil");
	setCameraMode(1);
	LOGMSG("-------- initializing physics --------");
	sphere = new btSphereShape(GetFloat("sphere_radius"));
	//Nodes.push_back(scmgr->getSceneNode("target"));
	size_t sz = Nodes.size();
	for(size_t i = 0; i < sz; ++ i)
		add_col_obj(i);
	init_bullets();
#ifndef LASERCAST
	init_laser();
#endif
	LOGMSG("------- initializing inputs and GUI -------");
	init_inputs();
	init_gorilla();
	
	mat //= scmgr->getEntity("bonome")->getMaterial();
	= scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial();
	colorval1 = ColourValue(0.2f,0.f,0.f);
	colorval2 = ColourValue(0.f,0.f,0.2f);

	//material_hover = create_hover_material
	//	(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());

	LOGMSG("-------- reading parameters from config-file --------"); 
	translate			= Vec3 (0.0f,0.0f,0.0f);
	translate2			= Vec3 (0.0f,0.0f,0.0f);
	rotating_speed		= GetFloat ("rotating_speed");
	moving_speed		= GetFloat ("moving_speed");
	stop				= false;
	offset				= GetVect3("offset");

	LOGMSG("-------- misc ogre parameters --------"); 
	window -> reposition(20, 20);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	LOGMSG("-------- simple crosshair --------"); 
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();

	init_procedural();
	LOGMSG("colobj: "+TO_STR(colw->getCollisionObjectArray().size()));
	LOGMSG("Nodes: "+TO_STR(Nodes.size()));
	LOGMSG("Entities: "+TO_STR(Entities.size()));
	LOGMSG("sizeof app class: "+TO_STR(sizeof(Application)));

	LOGMSG("-----------------------------------------------------------------");
	LOGMSG("        FINISHED INITIALIZING OGRE3D; begginning gameloop        ");
	LOGMSG("-----------------------------------------------------------------");
}



void Application :: add_debug_gizmo(string name)
{
	// laser DOT
	//BillboardSet * white_dot[16];
	//Billboard * gizmo[16];
	{
		float laserdot_scale = GetFloat("dotscale");
		n_root -> createChildSceneNode(name)
			-> attachObject (scmgr -> createBillboardSet(name));

		scmgr->getSceneNode(name) -> setScale(Vec3(laserdot_scale,laserdot_scale,laserdot_scale));
		scmgr->getBillboardSet(name)-> createBillboard(Ogre :: Vector3(0, 0, 0));

		switch(diagnose_vect.size()%3)
		{
		case 0: scmgr->getBillboardSet(name) -> setMaterialName("jokoon/gizmo"); break;
		case 1: scmgr->getBillboardSet(name) -> setMaterialName("jokoon/gizmo2"); break;
		case 2: scmgr->getBillboardSet(name) -> setMaterialName("jokoon/gizmo3"); break;
		default:break;
		}

	//n_laserdot	 = n_root -> createChildSceneNode("laser dot");
	//bb_laserdot	 = scmgr  -> createBillboardSet("laser dot");
	//n_laserdot -> attachObject (bb_laserdot);
	//bb_laserdot -> setMaterialName("jokoon/laser_dot");
	//float laserdot_scale = GetFloat("dotscale");
	//n_laserdot -> setScale(Vec3(laserdot_scale,laserdot_scale,laserdot_scale));
	//bboard		 = bb_laserdot -> createBillboard(Ogre :: Vector3(0, 0, 0));


	}
}