//#ifndef __APPLE__
#include "stdafx.h"
//#endif
typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{
#ifndef FOLD_THIS
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

	void LoadEntity(string);
	SceneNode * AddLevel(string);
	SceneNode * AddLight(string);
	SceneTypeMask GetScMgrType();
	Vec3 GetVect3(string _s);

	void Populate();
	void handle_bullet();
	void check_collisions();
	void moveTo(int entity_id, Vec3 dest, float speed = 3.f);
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
#endif
    CameraController * cam_ctrlr;	
	game_machine * machine;
	float sphere_radius_squared;
	Vec3 temp;
	std::vector<Entity *> Entities;
	std::vector<SceneNode *> Nodes;
	std::vector<Vec3> velocities;
	std::vector<bool> isMoving;
    Entity * entplane;
    SceneNode * rootnode;

	Gorilla :: Silverback	* mGorilla;
	Gorilla :: Screen		* gor_screen;
	Gorilla :: Rectangle	* gor_rect;
	Gorilla :: Layer		* gor_layer;
	Gorilla :: Caption		* gor_caption[15];
	OgreConsole * console;
	
#ifdef PHYSICS
    btBroadphaseInterface				* broadphase;
    btDefaultCollisionConfiguration		* collisionConfiguration;
    btCollisionDispatcher				* dispatcher;
	btCollisionWorld					* collisionWorld;

	btCollisionWorld :: ContactResultCallback * result;
	btTransform transf;
	btSphereShape * sphere;

#endif

	//Material * hover_idle, hover_hover;
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif
};

