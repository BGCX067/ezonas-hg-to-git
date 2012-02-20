#include "stdafx.h"

typedef RaySceneQueryResult :: iterator RSQR_iter_t;
struct Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{
	// singleton
	static Application * getSingletonPtr(void);
	static Application * Instantiate();

	// interface
	// config file reading
	static string str_vect(Vec3 v) { return TO_STR(v.x) + " " + TO_STR(v.y)+ " " + TO_STR(v.z); }
	static string str_quat(Quaternion q) { return TO_STR(q.w)+" "+TO_STR(q.x)+" "+TO_STR(q.y)+" "+TO_STR(q.z); }
	float	GetFloat	(string);
	int		GetInt		(string _s);
	Vec3	GetVect3	(string _s);
	Ogre::Vector2 GetVect2(string _s);

	// ####### data loading #######
	SceneTypeMask GetScMgrType();
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);

	// ####### getters #######
	SceneManager *		GetScMgr()	{ return scmgr;						   }
	SceneNode *			GetRSN()	{ return scmgr -> getRootSceneNode();  }
	Camera *			GetCam()	{ return camera;					   }
	RenderWindow *		GetRW()		{ return window;					   }
	Ogre::ConfigFile *	GetCFG()	{ return configfile;				   }

	// ####### overloading #######
	bool frameRenderingQueued(const FrameEvent & evt);
	bool frameStarted(const FrameEvent & evt);
	bool frameEnded(const FrameEvent & evt);

    void go();
	float timeSinceLastFrame;

	Application();
    ~ Application();

	// ####### inside the game loop #######
	void handle_bullet();
	void check_collisions();
	void moveTo(int entity_id, Vec3 dest, float speed = 3.f);

	// ####### at loading #######
	void initialize();
	void Populate();
	void LoadEntity(string);

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
	
	// ################### bullet physics ###################
    btBroadphaseInterface			* broadphase;
    btDefaultCollisionConfiguration	* collisionConfig;
    btCollisionDispatcher			* dispatcher;
	btCollisionWorld				* collisionWorld;
	//btCharacterControllerInterface * char_ctrl;

	// ################### gorilla (GUI) ###################
	Gorilla :: Silverback	* mGorilla;
	Gorilla :: Screen		* gor_screen;
	Gorilla :: Rectangle	* gor_rect;
	Gorilla :: Layer		* gor_layer;
	Gorilla :: Caption		* gor_caption[15];
	OgreConsole * console;

	// ################### custom ###################
    CameraController * cam_ctrlr;
	game_machine * machine;

	// ################### effects ###################
	LaserCast * lasercast;
	BulletTracer * bullet_tracer;

	// temporary vectors and pointers
	Entity * entplane;//, * last_entity_raycast, * current_ent_raycast;
    SceneNode * rootnode;
	
	// intermediate Ogre/bullet data
	Vec3 temp;
	btMatrix3x3 mat3_zero;		   // warning :
	btTransform transf;			   // the order of those 2 object matters
	btCollisionWorld :: ContactResultCallback * result;
	btSphereShape * sphere;

	// data
	float sphere_radius_squared;
	MaterialPtr material_hover;

	// tracks of entities, nodes, velocities and other
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;
	std::vector<Vec3> velocities;
	std::vector<bool> isMoving;
	short index[1024];
};

