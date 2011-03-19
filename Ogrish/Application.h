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
    void go();
    bool frameRenderingQueued(const FrameEvent & evt);
	static Application * Instantiate();
/* ############ PRIVATE ############ */
private:
	bool init_config();
    void CreateScene();
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
    FPersonCam * fpersoncam;
	
	// overlays
	OverlayManager * ovl_mgr;
	//Overlay * ovl_crosshair;

    // entities and nodes
    Entity * entplane;
    SceneNode * rootnode;

	// terrain
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif
};

