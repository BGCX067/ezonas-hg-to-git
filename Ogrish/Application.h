#include "stdafx.h"

typedef RaySceneQueryResult :: iterator RSQR_iter_t;
struct Application:
	public FrameListener,
	public OIS::KeyListener,
	public OIS::MouseListener
{
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
	float smoothstep(float x);
	float smoothstep2(float,float,float);
	float smoothstep_fast(float x);
	float weight_avg(float x, float goal, float slowdown);


	// ####### various functions #######
	void setCameraMode(int mode);
	void Fire();
	void calculate_recoil();
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

	// ####### bullet physics #######
    btBroadphaseInterface			* broadphase;
    btDefaultCollisionConfiguration	* collisionConfig;
    btCollisionDispatcher			* dispatcher;
	btCollisionWorld				* colw;
	//btCharacterControllerInterface * char_ctrl;
	BtOgre::StaticMeshToShapeConverter * mesh2shape;
	btCollisionWorld::ClosestRayResultCallback raycallback;

	Vec3 from, to;
	btVector3 btfrom, btto;
	btSphereShape * sphere;

	// ####### gorilla (GUI) #######
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
	// ####### OIS #######
	OIS::InputManager * inputmanager;
	OIS::Keyboard * keyboard;
	OIS::Mouse * mouse;

	// ####### custom #######
	game_machine * machine;
	LaserCast * lasercast;
	// ####### camera system #######
	int camera_mode;
	uchar recoil_shot_acc, current_recoil;
	float moving_speed, rotating_speed,
		timeSinceLastFrame,
		laser_width,
		recoil_yaw, recoil_pitch,
		recoil_yaw_factor, recoil_pitch_factor,
		recoil_factor, recoil_c,
		recoil_threshold,
		time_buffer[32]
		;
	bool stop;
	Vec3 offset;
	Vec3 translate, translate2;
	Quaternion rotate;
	Entity * e_target;

	SceneNode
		* n_root	,
		* n_master  ,	 // those 3 in this exact order
		* n_target	,	 // those 3 in this exact order
		* n_cam		,	 // those 3 in this exact order
		* n_yawpitch_ptr, // this node will serve as a pointer to switch between 1st/rd person cam
		* n_recoil;
	// etc
	Entity * entplane;//, * last_entity_raycast, * current_ent_raycast;
	MaterialPtr mat;
	ColourValue colorval1;
	ColourValue colorval2;

	// ####### bullets #######
	BillboardChainFactory bbchfact;
	BillboardChain * MakeABullet(string);
	ushort nextbullet;
	float bullet_speed,
		time_stack, fire_delay,
		offset_x, offset_y;
	Vec3 ray_start, ray_end;
	btVector3 arg_start, arg_end;
	bool was_fired, trigger_state;
	BillboardChain * bb_trace_model;
	Entity
		* ent_check,
		* last_entity,
		* current_entity;
	//#ifdef USE_ARRAYS
	//	SceneNode * n_bullet [BULLET_MAX];
	//	BillboardSet * bb_dot[BULLET_MAX];
	//	BillboardChain * bb_trace[BULLET_MAX];
	//	btCollisionWorld :: ClosestRayResultCallback raycast_callback[BULLET_MAX];
	//#endif
	std::vector<SceneNode *		>	n_bullet ;
	std::vector<BillboardSet *	>	bb_dot	 ;
	std::vector<BillboardChain *>	bb_trace;
	std::vector<bullet_raycast>		callbacks;
	// ####### laser #######
	SceneNode
		* n_laserdot,
		* n_laserbeam;
		Ray ray_cam;
	RaySceneQuery * RSQ;
	RaySceneQueryResult RSQR;
	BillboardSet * bb_laserdot;
	Billboard * bboard;
	BillboardChain * bb_beam;

	// debugging
	std::map<std::string, Vec3> diagnose_vect;
};

