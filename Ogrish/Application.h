//#ifndef __APPLE__
#include "stdafx.h"
//#endif
typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{

public: /* ############ PUBLIC ############ */
    static Application * getSingletonPtr(void);
	static string str_vect(Vec3 v) { return TO_STR(v.x) + " " + TO_STR(v.y)+ " " + TO_STR(v.z); }
	static string str_quat(Quaternion q) { return TO_STR(q.w) + " " + TO_STR(q.x) + " " + TO_STR(q.y)+ " " + TO_STR(q.z); }

	float frame_time;

	// getters
	SceneManager * GetScMgr();
    SceneNode * GetRSN();
	Camera * GetCam();
	RenderWindow * GetRW();
	Ogre::ConfigFile * GetCFG();
	float * GetFT();

    void go();
    bool frameRenderingQueued(const FrameEvent & evt);
	static Application * Instantiate();
	float GetFloat(string);
	int GetInt(string _s);

	
	void LoadAttachEntity(string);
	void LoadEntity(string); // those 2 functions are the same, the first just attach to a same named node
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);
	SceneTypeMask GetScMgrType();
	Vec3 GetVect3(string _s);


protected:
private: /* ############ PRIVATE ############ */
	bool init_config();
    void CreateScene();
	void InitGorilla();
	void AddLights();
	void InitResources();
#ifdef USE_TERRAIN
    void CreateTerrain();
#endif
	Application();
    ~ Application();
    void AddPlane();
	/* ############ PRIVATE VARIABLES ############ */
	// ######## EVERYTHING OGRE ########
    // Ogre core objects: remember that the order they are declared MATTERS !
    Root * root;

	bool last_init; // some flag to allow constructor init syntax

	// actual ogre objects
	RenderWindow * window;
    SceneManager * scmgr;
    Camera * camera;
    Viewport * viewport;

	ConfigFile * configfile;

	// ######## OTHER CLASSES ########
	// game
    CameraController * cam_ctrlr;
    //Cam3rdperson * cam3rdperson;
	
	game_machine * machine;
	// overlays
	// OverlayManager * ovl_mgr;
	// Overlay * ovl_crosshair;

	// entities and nodes
	std::map <string, SceneNode *> Nodes;
	std::vector<Entity *> Entities;
    Entity * entplane;
    SceneNode * rootnode;

	// ######## gorilla objects ########
	Gorilla :: Silverback * mGorilla;
	Gorilla :: Screen * gor_screen;
	Gorilla :: Rectangle * gor_rect;
	Gorilla :: Layer * gor_layer;
	Gorilla :: Caption * gor_caption[15];
	//Gorilla :: MarkupText * gor_mutext;
	// terrain
	
// ######## bullet physics ########
#ifdef PHYSICS
    // Build the broadphase
    btBroadphaseInterface* broadphase;// = new btDbvtBroadphase();
    // Set up the collision configuration and dispatcher
    btDefaultCollisionConfiguration* collisionConfiguration;// = new btDefaultCollisionConfiguration();
    btCollisionDispatcher* dispatcher;// = new btCollisionDispatcher(collisionConfiguration);
    // The actual physics solver
    //btSequentialImpulseConstraintSolver* solver;// = new btSequentialImpulseConstraintSolver;
    // The world.
    //btDiscreteDynamicsWorld* dynamicsWorld;// = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
	btCollisionWorld * collisionWorld;// = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
#endif


// terrain manager
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif
};

