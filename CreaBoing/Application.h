#include "stdafx.h"

//typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{
/* ############ PUBLIC ############ */
public:
    static Application * getSingletonPtr(void);

	float frame_time;
    //static Application * sglt();
    SceneManager * GetScMgr();
    SceneNode * GetRSN();
	Camera * GetCam();
	RenderWindow * GetRW();
	float * GetFT();
    void go();
    bool frameRenderingQueued(const FrameEvent & evt);
	static Application * Instantiate();
/* ############ PRIVATE ############ */
private:
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
	
    // Ogre core objects: remember that the order they are declared MATTERS !
    Root * root;

	bool last_init;

	RenderWindow * window;
    SceneManager * scmgr;
    Camera * camera;
    Viewport * viewport;

// game parameters
    CameraController * cam_ctrlr;
    //Cam3rdperson * cam3rdperson;
	
// overlays
	OverlayManager * ovl_mgr;
//Overlay * ovl_crosshair;

// entities and nodes
    Entity * entplane;
    SceneNode * rootnode;

// gorilla


	Gorilla :: Silverback * mGorilla;
	Gorilla :: Screen * gor_screen;
	Gorilla :: Rectangle * gor_rect;
	Gorilla :: Layer * gor_layer;
	Gorilla :: Caption * gor_caption[15];
	//Gorilla :: MarkupText * gor_mutext;
	// terrain
/* bullet physics */
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



#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif

#ifdef CREABOING
	Vec3 velocity, accel, position, gravity;
	SceneNode * n_ball;
	Entity * e_ball;
	float ground_height, y;
	void UpdatePhysics();
#endif
};

