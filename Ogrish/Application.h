//#ifndef __APPLE__
#include "stdafx.h"
//#endif
typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{
public: /* ######################## PUBLIC ######################## */
	// singleton
	static Application * getSingletonPtr(void);
	static Application * Instantiate();

	// interface
	// config file reading
	static string str_vect(Vec3 v) { return TO_STR(v.x) + " " + TO_STR(v.y)+ " " + TO_STR(v.z); }
	static string str_quat(Quaternion q) { return TO_STR(q.w) + " " + TO_STR(q.x) + " " + TO_STR(q.y)+ " " + TO_STR(q.z); }
	float GetFloat(string);
	int GetInt(string _s);
	Vec3 GetVect3(string _s);
	Ogre::Vector2 GetVect2(string _s);

	// data loading
	SceneTypeMask GetScMgrType();
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);

	// getters
	SceneManager * GetScMgr();
    SceneNode * GetRSN();
	Camera * GetCam();
	RenderWindow * GetRW();
	Ogre::ConfigFile * GetCFG();
	float * GetFT();

	// overloading
	bool frameRenderingQueued(const FrameEvent & evt);
	bool frameStarted(const FrameEvent & evt);
	bool frameEnded(const FrameEvent & evt);

    void go();
	float frame_time;

protected:
private: /* ######################## PRIVATE ######################## */

	Application();
    ~ Application();

	// inside the game loop
	void handle_bullet();
	void check_collisions();
	void moveTo(int entity_id, Vec3 dest, float speed = 3.f);

	void initialize();
	void init_physics();
	void Populate();
	void LoadEntity(string);

    void CreateScene();
	void InitGorilla();
	void AddLights();
	void InitResources();
#ifdef USE_TERRAIN
    void CreateTerrain();
#endif
    void AddPlane();
	/* ######################## VARIABLES ######################## */
	// ######## EVERYTHING OGRE ########
    // Ogre core objects: remember that the order they are declared MATTERS !
    Root * root;

	// actual ogre objects
	RenderWindow * window;
    SceneManager * scmgr;
    Camera * camera;
    Viewport * viewport;
	ConfigFile * configfile;

	// custom objects
    CameraController * cam_ctrlr;
    Entity * entplane;
    SceneNode * rootnode;

	// effect objects
	LaserCast * lasercast;
	BulletTracer * bullet_tracer;

	// game state machine
	game_machine * machine;

#ifdef PHYSICS
	// bullet physics
    btBroadphaseInterface				* broadphase;
    btDefaultCollisionConfiguration		* collisionConfiguration;
    btCollisionDispatcher				* dispatcher;
	btCollisionWorld					* collisionWorld;

#endif
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif

	// gorilla (GUI)
	Gorilla :: Silverback	* mGorilla;
	Gorilla :: Screen		* gor_screen;
	Gorilla :: Rectangle	* gor_rect;
	Gorilla :: Layer		* gor_layer;
	Gorilla :: Caption		* gor_caption[15];
	OgreConsole * console;

	// data
	float sphere_radius_squared;
	MaterialPtr hover_idle, hover_hover;
#ifdef PHYSICS
	// intermediate Ogre/bullet data
	Vec3 temp;
	btMatrix3x3 mat3_zero;		   // warning :
	btTransform transf;			   // the order of those 2 object matters
	btCollisionWorld :: ContactResultCallback * result;
	btSphereShape * sphere;
#endif


	// tracks of entities, nodes, velocities and other
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;
	std::vector<Vec3> velocities;
	std::vector<bool> isMoving;



};

