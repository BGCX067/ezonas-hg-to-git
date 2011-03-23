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
	void InitGorilla();
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
    FPersonCam * fpersoncam;
	
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
#ifdef USE_TERRAIN
	Ogre::Terrain * mTerrain;
	Ogre::TerrainGlobalOptions * mGlobals;
#endif
};

