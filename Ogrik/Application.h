#include "stdafx.h"

class OgrikFrameListener;

typedef RaySceneQueryResult :: iterator RSQR_iter_t;

class Application: public FrameListener
{
public:
    // enum state_ctrl_mode {FPS, CURSOR} ctrl_mode;
    // void renderOneFrame();
    static Application * GetSingleton();//	{return instance;}
    static SceneManager * GetScMgr();//	{return instance;}
    static void Instantiate();// {static Application inst; instance = & inst;}
    void go();
// added those 3 lines
    bool frameRenderingQueued(const FrameEvent & evt);
private:
    SceneNode * QuickAdd(string str);

    static Application * instance;
    void createScene();
    Application();
    ~ Application();
    void AddPlane();

    // Ogre core objects
    static SceneManager * scenemanager;
    Root * root;
    RenderWindow * window;
    Camera * camera;
    Viewport * viewport;

    // game parameters
    FPersonCam * fpersoncam;

    // entities and nodes
    Entity * sinbad, * entplane;
    SceneNode * rootnode;
};

