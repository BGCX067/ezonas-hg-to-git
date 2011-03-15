#include "stdafx.h"

class OgrikFrameListener;

typedef RaySceneQueryResult :: iterator RSQR_iter_t;

class Application: public FrameListener
{
public:
	float frame_time;
    static Application * sglt();
    SceneManager * GetScMgr();
    SceneNode * GetRSN();
	Camera * GetCam();
	RenderWindow * GetRW();
    void go();
    bool frameRenderingQueued(const FrameEvent & evt);
private:
    void CreateScene();
#ifdef USE_TERRAIN
    void CreateTerrain();
#endif
	Application();
    ~ Application();
    void AddPlane();
	
    // Ogre core objects: remember that the order they are declared MATTERS !
    Root * root;
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

