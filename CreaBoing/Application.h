#include "stdafx.h"

//typedef RaySceneQueryResult :: iterator RSQR_iter_t;
class Application:
	public FrameListener,
	public Ogre :: Singleton <Application>
{
/* ############ PUBLIC ############ */
public:
    static Application * getSingletonPtr(void);
	Vec3 * GetVelocityAddress();
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
    Entity * entplane[30][30];
    SceneNode * rootnode;

	Gorilla :: Silverback * mGorilla;
	Gorilla :: Screen * gor_screen;
	Gorilla :: Rectangle * gor_rect;
	Gorilla :: Layer * gor_layer;
	Gorilla :: Caption * gor_caption[15];


#ifdef CREABOING
	Vec3 velocity, accel, position, gravity, vel_prev, pos_prev, acc_prev, forces, impact;
	SceneNode * n_ball;
	Entity * e_ball;
	float y;
	int cell_x, cell_z, grid_size;

	void UpdatePhysics();
	Plane planes[100];
	SceneNode * nodes[100], * n_plane;
#endif
};

