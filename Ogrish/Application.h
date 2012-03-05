#include "stdafx.h"

typedef RaySceneQueryResult :: iterator RSQR_iter_t;
struct Application:
	public FrameListener,
	public KeyListener,
	public MouseListener
{
	// config file reading
	static string str_vect(Vec3 v)
	{ return TO_STR(v.x) + " " + TO_STR(v.y)+ " " + TO_STR(v.z); }
	static string str_quat(Quaternion q)
	{ return TO_STR(q.w)+" "+TO_STR(q.x)+" "+TO_STR(q.y)+" "+TO_STR(q.z); }
	float	GetFloat		(string _s);
	int		GetInt			(string _s);
	Vec3	GetVect3		(string _s);
	string	GetString		(string _s);
	Ogre::Vector2 GetVect2	(string _s);

	// ####### data loading #######
	SceneTypeMask GetScMgrType();
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);
	
	// ####### overloading #######
	bool frameRenderingQueued(const FrameEvent & evt);
	bool frameStarted(const FrameEvent & evt);
	bool frameEnded(const FrameEvent & evt);

    void go();
	Application();
    ~ Application();

	// ####### everything about physics/bullet #######
	void loop_bullet(); // in game loop
	void init_bullet(); // at loading
	void moveTo(ushort idx, Vec3 dest, float speed = 3.f);
	void add_col_obj(size_t);
	//void check_collisions();

	// ####### called at loading #######
	void init_engines();
	void init_scene();
	void init_bullets();
	void Populate();
	void LoadEntity(string);
	
	void loadlist();
	void InitGorilla();
	void AddLights();
	void InitResources();

	MaterialPtr create_hover_material(MaterialPtr mat);
    void AddPlane();

	// ################### actual ogre objects ###################
	Root			* root;
	RenderWindow 	* window;
    SceneManager 	* scmgr;
    Camera 			* camera;
    Viewport 		* viewport;
	ConfigFile 		* configfile;

	// ################### OIS ###################
	InputManager * inputmanager;
	Keyboard * keyboard;
	Mouse * mouse;
	void init_inputs();
	
	bool mouseMoved		(const OIS::MouseEvent &e);
	bool mousePressed	(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool mouseReleased	(const OIS::MouseEvent &e, OIS::MouseButtonID id);
	bool keyPressed		(const OIS::KeyEvent &e);
	bool keyReleased	(const OIS::KeyEvent &e);
	
	// ################### bullet physics ###################
    btBroadphaseInterface			* broadphase;
    btDefaultCollisionConfiguration	* collisionConfig;
    btCollisionDispatcher			* dispatcher;
	btCollisionWorld				* collisionWorld;
	//btCharacterControllerInterface * char_ctrl;
	BtOgre::StaticMeshToShapeConverter * mesh2shape;

	// ################### gorilla (GUI) ###################
	Gorilla :: Silverback	* mGorilla;
	Gorilla :: Screen		* gor_screen;
	Gorilla :: Rectangle	* gor_rect;
	Gorilla :: Layer		* gor_layer;
	Gorilla :: Caption		* gor_caption[15];
	OgreConsole * console;

	// ################### camera system ###################
	void setCameraMode(int mode);
	int camera_mode;
	float moving_speed, rotating_speed, timeSinceLastFrame, rot;
	bool stop;
	Vec3 offset;
	Vec3 translate, translate2;
	
	Entity * e_target;

	SceneNode
		* n_root	,
		* n_master  ,	 // those 3 in this exact order
		* n_target	,	 // those 3 in this exact order
		* n_cam		,	 // those 3 in this exact order
		* n_yawpitch_ptr; // this node will serve as a pointer to switch between 1st/rd person cam
	// ################### custom ###################
	game_machine * machine;

	// ################### bullets ###################
	void Fire();
	void update_bullets();
	BillboardChainFactory bbchfact;
	BillboardChain * MakeABullet(string);
	ushort nextbullet;
	float bullet_speed,
		trace_width, trace_length,
		time_stack, fire_delay,
		offset_x, offset_y;
	Vec3 ray_start, ray_end;
	btVector3 arg_start, arg_end;
	bool was_fired;
	BillboardChain * bb_bullet_model;
	Entity
		* ent_check,
		* last_entity,
		* current_entity;
//#ifdef USE_ARRAYS
//	SceneNode * n_bullet [BULLET_MAX];
//	BillboardSet * bb_dot[BULLET_MAX];
//	BillboardChain * bb_bullet[BULLET_MAX];
//	btCollisionWorld :: ClosestRayResultCallback raycast_callback[BULLET_MAX];
//#endif
	std::vector<SceneNode *		>	n_bullet ;
	std::vector<BillboardSet *	>	bb_dot	 ;
	std::vector<BillboardChain *>	bb_bullet;
	std::vector<bullet_raycast>		callbacks;
	// temporary vectors and pointers
	Entity * entplane;//, * last_entity_raycast, * current_ent_raycast;
	
	// intermediate Ogre/bullet data
	Vec3 temp, temp1;
	btMatrix3x3 mat3_zero;		   // warning :
	btTransform transf;			   // the order of those 2 object matters
	btCollisionWorld :: ContactResultCallback * result;
	btSphereShape * sphere;

	// data
	float sphere_radius_squared;
	MaterialPtr material_hover;
	// Start and End are vectors
 
	// tracks of entities, nodes, velocities and other
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;
	std::vector<Vec3> velocities;
	std::vector<bool> isMoving;
	std::vector<bool> hasCollided;
};

