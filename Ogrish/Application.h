#include "stdafx.h"

//typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{

public: /* ############ PUBLIC ############ */
    static Application * getSingletonPtr(void);

	float frame_time;

    //static Application * sglt();
	// getters for ogre objects
	SceneManager * GetScMgr();
    SceneNode * GetRSN();
	Camera * GetCam();
	RenderWindow * GetRW();
	float * GetFT();
    void go();
    bool frameRenderingQueued(const FrameEvent & evt);
	static Application * Instantiate();
		float GetFloat(string);
	int GetInt(string _s);

	// quickly add a model by it's filename without .mesh naming the node the same
	void LoadAttachEntity(string);
	void LoadEntity(string); // those 2 functions are the same, the first just attach to a same named node
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);
	SceneTypeMask GetScMgrType();
	Vec3 & GetVect3(string _s);

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
	
	Game_machine * game_machine;
	// overlays
	OverlayManager * ovl_mgr;
	//Overlay * ovl_crosshair;

	// entities and nodes
	std::map <string, SceneNode *> Nodes;
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
    btSequentialImpulseConstraintSolver* solver;// = new btSequentialImpulseConstraintSolver;
    // The world.
    btDiscreteDynamicsWorld* dynamicsWorld;// = new btDiscreteDynamicsWorld(dispatcher,broadphase,solver,collisionConfiguration);
#endif


// terrain manager
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif
};

