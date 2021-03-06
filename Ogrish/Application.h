#include "stdafx.h"

typedef RaySceneQueryResult :: iterator RSQR_iter_t;
struct Application:
	public FrameListener,
	public OIS::KeyListener,
	public OIS::MouseListener
{
#ifndef _________METHODS_________
	///////////////////////////////////////////////////////////////////////////
	///////////////////////////////// METHODS /////////////////////////////////
	///////////////////////////////////////////////////////////////////////////

	Application();
    ~ Application();
    void go();

	// ####### overloading #######
	bool frameRenderingQueued(const FrameEvent & evt);
	bool frameStarted(const FrameEvent & evt);
	bool frameEnded(const FrameEvent & evt);

	// ####### OIS #######
	bool mouseMoved		(const OIS::MouseEvent &e);
	bool mousePressed	(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased	(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed		(const OIS::KeyEvent &e);
	bool keyReleased	(const OIS::KeyEvent &e);

	void update_physics(); // in game loop
	void moveTo(ushort idx, Vec3 dest, float speed = 3.f);
	void add_col_obj(size_t);
	//void check_collisions();

	// ####### math/interp functions #######
	float recoil(float);
	void recoil_event();
	float smoothstep(float x);
	float smoothstep2(float,float,float);
	float smoothstep_fast(float x);
	float weight_avg(float x, float goal, float slowdown);


	// ####### various functions #######
	void setCameraMode(int mode);
	void fire_trace();
	void trigger_pull();
	void trigger_release();

	void update_recoil();
	void update_bullets();
	void update_laser();
	void diagnose();

	// ####### initializing #######
	void init();
	void init_bullets();
	void init_laser();
	void init_inputs();
	void init_gorilla();
	void init_resources();
	void init_procedural();
	void add_debug_gizmo(string name);

	// ####### called at loading #######
	void Populate();
	void LoadEntity(string);
	void loadlevel(std::string);
	void loadlist();
    void AddPlane();
	void AddLights();
	MaterialPtr create_hover_material(MaterialPtr mat);
	SceneTypeMask GetScMgrType();
	SceneNode * AddLight(string);

	// config file reading
	float	GetFloat	(string _s);
	int		GetInt		(string _s);
	Vec2	GetVect2	(string _s);
	Vec3	GetVect3	(string _s);
	string	GetString	(string _s);
	static string str_vect(Vec3 v)
	{ return TO_STR(v.x) + " " + TO_STR(v.y)+ " " + TO_STR(v.z); }
	static string str_quat(Quaternion q)
	{ return TO_STR(q.w)+" "+TO_STR(q.x)+" "+TO_STR(q.y)+" "+TO_STR(q.z); }

#endif
#ifndef _________DATA_________
	///////////////////////////////////////////////////////////////////////////
	/////////////////////////////////// DATA //////////////////////////////////
	///////////////////////////////////////////////////////////////////////////
	// ####### actual ogre objects #######
	Root			* root;
	RenderWindow 	* window;
    SceneManager 	* scmgr;
    Camera 			* camera;
    Viewport 		* viewport;
	ConfigFile 		* configfile;

	std::vector<void *> delete_it;
	// ------------------------------
	// ####### bullet physics #######
	// ------------------------------
    btBroadphaseInterface			* broadphase;
    btDefaultCollisionConfiguration	* collisionConfig;
    btCollisionDispatcher			* dispatcher;
	btCollisionWorld				* colw;
	//btCharacterControllerInterface * char_ctrl;
	BtOgre::StaticMeshToShapeConverter * mesh2shape;
	btCollisionWorld::ClosestRayResultCallback raycallback;
	BtOgre::DebugCollisionDrawer * col_dgb;
	
	Ogre::Entity		 * e_ground;

	Vec3 from, to;
	btVector3 btfrom, btto;
	btSphereShape * sphere;

	// ------------------------------
	// ####### gorilla (GUI) #######
	// ------------------------------
	Gorilla :: Silverback	* mGorilla;
	Gorilla :: Screen		* gor_screen;
	Gorilla :: Rectangle	* gor_rect;
	Gorilla :: Layer		* gor_layer;
	Gorilla :: Caption		* gor_caption[15];
	OgreConsole * console;

	// ####### entities, nodes, velocities and other #######
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;
	std::vector<Vec3> velocities;
	std::vector<bool> isMoving;
	std::vector<bool> hasCollided;
	// ------------------------------
	// ####### OIS #######
	// ------------------------------
	OIS::InputManager * inputmanager;
	OIS::Keyboard * keyboard;
	OIS::Mouse * mouse;

	// ------------------------------
	// ####### custom #######
	// ------------------------------
	game_machine * machine;
	LaserCast * lasercast;
	int camera_mode;
	uchar
		recoil_shot_acc,
		current_recoil,
		nextbullet,
		auto_shots_fired
		;
	float
		moving_speed,
		rotating_speed,
		timeSinceLastFrame,
		laser_width,
		bullet_speed,
		time_stack,
		fire_delay,
		offset_x, offset_y,
	
		// recoil
		recoil_pitch, recoil_yaw,
		kickback,
		recoil_cap,
		cooldown_step;
		/*quickness_const,		
		time_shot_event,
		time_since_last_shot,
		time_buffer[32],
		quickness[32],
		time_between_shots,
		previous_fading_recoil*/
		
	bool
		stop,
		//time_buffer_enable[32],
		trigger_pulled;
	Vec3
		offset,
		ray_start,
		ray_end,
		translate,
		translate2;
	btVector3 arg_start, arg_end;
	Quaternion rotate;
	Entity
		* e_target,
		* entplane,
		* ent_check,
		* last_entity,
		* current_entity;

	SceneNode
		* n_root	,
		* n_master  ,	 
		* n_target	,	 
		* n_cam		,	 
		* n_yawpitch_ptr, // this node will serve as a pointer to switch between 1st/rd person cam
		* n_recoil,
		* n_laserdot,
		* n_laserbeam;

	MaterialPtr mat;
	ColourValue colorval1;
	ColourValue colorval2;

	// ------------------------------
	// ####### bullets #######
	// ------------------------------
	BillboardChainFactory bbchfact;
	BillboardChain * MakeABullet(string);
	BillboardSet * bb_laserdot;
	Billboard * bboard;
	BillboardChain
		* bb_beam,
		* bb_trace_model;

	std::vector<SceneNode *		>	n_bullet ;
	std::vector<BillboardSet *	>	bb_dot	 ;
	std::vector<BillboardChain *>	bb_trace;
	std::vector<bullet_raycast>		callbacks;

	Ray ray_cam;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;

	std::map<std::string, Vec3> diagnose_vect;
	std::map<std::string, float> diagnose_float;
#endif
};

