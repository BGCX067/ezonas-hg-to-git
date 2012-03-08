#include "stdafx.h"

void Application :: add_col_obj(size_t index)
{
	assert(index < Nodes.size());

	btCollisionObject * colobj = new btCollisionObject;
	colobj->setCollisionShape(sphere);
//	temp = Nodes[index] -> getPosition();
	temp = Nodes[index] -> _getDerivedPosition();
	colobj -> getWorldTransform().setOrigin(btVector3(temp.x, temp.y, temp.z));
	colobj -> setUserPointer(Nodes[index]);
	colw -> addCollisionObject(colobj);
	hasCollided.push_back(false);
}
void Application :: init_bullets()
{
	bullet_speed = GetFloat("bullet_speed");
	nextbullet	 = 0;
	was_fired	 = false;
	trigger_state= false;
	time_stack	 = 0;
	fire_delay	 = GetFloat("fire_delay");
	offset_x	 = GetFloat("offset_x");
	offset_y	 = GetFloat("offset_y");
	
	n_bullet	.resize(BULLET_MAX);
	bb_dot		.resize(BULLET_MAX);
	bb_trace	.resize(BULLET_MAX);
	callbacks	.resize(BULLET_MAX);

	float trace_width	 = GetFloat("trace_width");
	float trace_length = GetFloat("trace_length");

	
	FOR(BULLET_MAX)
	{
		// trace
		bb_trace[i] = (BillboardChain *) bbchfact.createInstance ("bullet"+TO_STR(i), scmgr);
		bb_trace[i] -> setMaterialName("jokoon/bullet_trace");
		bb_trace[i] -> setTextureCoordDirection(BillboardChain :: TCD_V);
		bb_trace[i] -> setUseTextureCoords(true);
		bb_trace[i] -> setMaxChainElements(2);
		bb_trace[i] -> addChainElement (0, BillboardChain::Element
			(Vec3(0, 0, 0), trace_width, 0, ColourValue()));
		bb_trace[i] -> addChainElement (0, BillboardChain::Element
			(Vec3(0, 0, trace_length), trace_width, 0, ColourValue()));
		// dot
		bb_dot[i] = scmgr -> createBillboardSet();
		bb_dot[i] -> createBillboard(Vec3(0,0,0));
		bb_dot[i] -> setMaterialName("jokoon/bullet_dot");
		float scale = GetFloat("bullet_dot");
		bb_dot[i]
			-> getMaterial() -> getTechnique(0u) -> getPass(0u)
			-> getTextureUnitState(0u) -> setTextureScale(scale, scale);
		// nodes
		n_bullet[i] = n_root -> createChildSceneNode("bullet"+TO_STR(i));
		n_bullet[i] -> attachObject(bb_trace[i]);
		n_bullet[i] -> attachObject(bb_dot[i]);
	}
}
void Application :: init_laser()
{
	ray_cam		 = Ray(Vec3(0, 0, 0), Vec3(-1, -1, -1));
	RSQ			 = scmgr -> createRayQuery(ray_cam);

	// laser DOT
	n_laserdot	 = n_root -> createChildSceneNode("laser dot");
	bb_laserdot	 = scmgr  -> createBillboardSet("laser dot");
	n_laserdot -> attachObject (bb_laserdot);
	bb_laserdot -> setMaterialName("jokoon/laser_dot");
	float laserdot_scale = GetFloat("dotscale");
	n_laserdot -> setScale(Vec3(laserdot_scale,laserdot_scale,laserdot_scale));
	//n_laserdot->setPosition(0.0, 5, 0);

	// laser BEAM
	float laser_width = GetFloat("laser_width");
	n_laserbeam  = n_root -> createChildSceneNode("laser beam");
	bboard		 = bb_laserdot -> createBillboard(Ogre :: Vector3(0, 0, 0));
	bb_beam		 = scmgr  -> createBillboardChain("laser beam");
	n_laserbeam -> attachObject (bb_beam);
	bb_beam -> setMaterialName("jokoon/laser_beam");
	bb_beam -> setMaxChainElements(2);
	bb_beam -> addChainElement (0, BillboardChain::Element
		(Vec3(0, 0, 100), laser_width, 0, ColourValue()));
	bb_beam -> addChainElement (0, BillboardChain::Element
		(Vec3(0, 0, 0), laser_width, 0, ColourValue()));
	bb_beam -> setUseTextureCoords(true);
	bb_beam -> setTextureCoordDirection(BillboardChain :: TCD_V);


}
void Application :: init()
{
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("                     INITIALIZING OGRE3D;                        ");
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("-------- loading resources.cfg --------");
	init_resources();

	PRINTLOG("------- allocating bullet objects -------");
	broadphase		= new btDbvtBroadphase();
    collisionConfig	= new btDefaultCollisionConfiguration();
    dispatcher		= new btCollisionDispatcher(collisionConfig);
	//solver		= new btSequentialImpulseConstraintSolver;
    //dynamicsWorld	= new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
    colw			= new btCollisionWorld(dispatcher,broadphase,collisionConfig);
	mesh2shape		= new BtOgre :: StaticMeshToShapeConverter;

	PRINTLOG("-------- allocating GUI, gameplay --------");
	mGorilla		= new Gorilla	:: Silverback();
	machine			= new game_machine;
#ifdef LASERCAST
	lasercast		= new LaserCast;
#endif
	// warning: some object's initialization depends on other, so *keep* this order
	// this is only required for core object, like camera node and character colobj
	// this is also required to populate objects before placing their colobj
	PRINTLOG("------- creating the scene -------");
	if (GetString("loadlevel")		 == "yes") loadlevel("level");
	if (GetString("Populate")		 == "yes") Populate();
	if (GetString("enable_loadlist") == "yes") loadlist();
	AddLight("light3");
	AddLight("light3b");
	AddPlane();
	LoadEntity("bonome");
	PRINTLOG("-------- creating camera scenenode tree and set camera mode --------");
	n_master = n_root   -> createChildSceneNode("master");
	n_target = n_master -> createChildSceneNode("target");
	n_cam	 = n_target -> createChildSceneNode("cam");
	setCameraMode(2);
	PRINTLOG("-------- initializing physics --------");
	sphere = new btSphereShape(GetFloat("sphere_radius"));
	//Nodes.push_back(scmgr->getSceneNode("target"));
	size_t sz = Nodes.size();
	for(size_t i = 0; i < sz; ++ i)
		add_col_obj(i);
	init_bullets();
	init_laser();
	PRINTLOG("------- initializing inputs and GUI -------");
	init_inputs();
	init_gorilla();
	
	mat //= scmgr->getEntity("bonome")->getMaterial();
	= scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial();
	colorval1 = ColourValue(0.2f,0.f,0.f);
	colorval2 = ColourValue(0.f,0.f,0.2f);

	//camera -> setFOVy(Radian(Degree(ConfMgr :: getSingletonPtr() -> GetFloat("fovy"))));

	//material_hover = create_hover_material
	//	(scmgr->getEntity("bonome")->getSubEntity(0)->getMaterial());
	

	PRINTLOG("-------- reading parameters from config-file --------"); 
	translate		= Vec3 (0.0f,0.0f,0.0f);
	translate2		= Vec3 (0.0f,0.0f,0.0f);
	rotating_speed	= GetFloat ("rotating_speed");
	moving_speed	= GetFloat ("moving_speed");
	stop			= false;
	offset			= GetVect3("offset");
	PRINTLOG("-------- misc ogre parameters --------"); 
	window -> reposition(20, 20);
	viewport -> setBackgroundColour(ColourValue(0.1f, 0.1f, 0.1f));
	PRINTLOG("-------- simple crosshair --------"); 
	if(GetInt("crosshair") == 1)
		OverlayManager :: getSingletonPtr() -> getByName("jokoon/crosshair") -> show();

	PRINTLOG("colobj: "+TO_STR(colw->getCollisionObjectArray().size()));
	PRINTLOG("Nodes: "+TO_STR(Nodes.size()));
	PRINTLOG("Entities: "+TO_STR(Entities.size()));
	PRINTLOG("sizeof app class: "+TO_STR(sizeof(Application)));
	PRINTLOG("-----------------------------------------------------------------");
	PRINTLOG("        FINISHED INITIALIZING OGRE3D; begginning gameloop        ");
	PRINTLOG("-----------------------------------------------------------------");
}


