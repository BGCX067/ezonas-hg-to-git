//
//  BaseFramework.m
//  OgreTest
//
//  Created by Penn Su on 2/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "BaseFramework.h"

BaseFramework::BaseFramework()
	: mRoot(0),
	mCamera(0),
	mSceneMgr(0),
	mWindow(0) {}
BaseFramework::~BaseFramework() {}

void BaseFramework::go() {
	if(!setup()) return;
	
	mRoot->startRendering();
	
	// clean up
	destroyScene();
}

bool BaseFramework::setup(void) {	
	std::string mResourcePath = [[[NSBundle mainBundle] resourcePath] cStringUsingEncoding:NSUTF8StringEncoding];
	
	// Create a new root object with the correct paths
	mRoot = new Root(mResourcePath + "/plugins.cfg", mResourcePath + "/ogre.cfg", mResourcePath + "/ogre.log");
	mRoot->setRenderSystem(mRoot->getAvailableRenderers().front());
	
	// Show a configure box and exit if user clicked cancel
	if(!mRoot->showConfigDialog()) return NO;
	
	// Initialise a window
	mWindow = mRoot->initialise(true);
	
	// Create SceneManager
	mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "My scene manager");
    
	// Setup and load Resources
	ResourceGroupManager::getSingleton().addResourceLocation(mResourcePath, std::string("FileSystem"), ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
	ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	
	createCamera();
	createViewports();
	
    // Set default mipmap level (NB some APIs ignore this)
    Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	
    // Create the scene
    createScene();
	
	return TRUE;
}

void BaseFramework::renderFrame()
{
	// Every time the timer fires, render a frame, and rotate the node
	Root::getSingleton().renderOneFrame();
	objectNode->yaw(Degree(1));
	//objectNode->rotate(Vector3(0, 1, 0), Radian(0.01));
}

bool BaseFramework::frameRenderingQueued(const FrameEvent& evt) {}

void BaseFramework::createCamera() {
	// Create the camera, node & attach camera
	mCamera = mSceneMgr->createCamera("My camera");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(mCamera);
	
	mCamera->setPosition(0, 50, 0);
	//mCamera->lookAt(Vector3(1963, 50, 1660));
	mCamera->setNearClipDistance(0.1);
	mCamera->setFarClipDistance(50000);
	if (mRoot->getRenderSystem()->getCapabilities()->hasCapability(RSC_INFINITE_FAR_PLANE))
		mCamera->setFarClipDistance(0);
}

void BaseFramework::createViewports() {
    // Create one viewport
	Viewport *vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(ColourValue(0, 0, 0));
	
	// Alter the camera aspect ratio to match the viewport
	mCamera->setAspectRatio(Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
}

void BaseFramework::createFrameListens() {
	mRoot->addFrameListener(this);
}

void BaseFramework::createScene() {
	
    // Set ambientlight and create a light
    mSceneMgr->setAmbientLight(ColourValue(0, 0, 0));
	
	Light *l = mSceneMgr->createLight("MainLight");
	l->setType(Light::LT_POINT);
	l->setDiffuseColour(ColourValue::White);
	l->setSpecularColour(ColourValue::White);
	l->setPosition(250, 150, 250);
	
    // Another light
	/*
	 Light *l2 = mSceneMgr->createLight("DirectionLight");
	 l2->setType(Light::LT_DIRECTIONAL);
	 l2->setDiffuseColour(ColourValue::White);
	 l2->setSpecularColour(0.7, 0.7, 0.7);
	 l2->setDirection(0.55, -0.3, 0.75);
	 */
	// Set shadow
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
	
    // Add multiple objects
    Entity *knot = mSceneMgr->createEntity("knot", "knot.mesh");
	knot->setCastShadows(true);
	
    objectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode", Vector3(0, 0, -500));
	objectNode->attachObject(knot);
    //objectNode->setPosition(Vector3(0, 0, -500));
	//objectNode->scale(.5, 1, 2);
	
    Entity *knot2 = mSceneMgr->createEntity("knot2", "knot.mesh");
	knot2->setCastShadows(true);
	
	mSceneMgr->getRootSceneNode()->createChildSceneNode("SecondNode", Vector3(200, 0, -800))->attachObject(knot2);
	
	// Creates a plane
	Plane plane(Vector3::UNIT_Y, 0);
	MeshManager::getSingleton().createPlane("ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, plane, 1500, 1500, 20, 20, true, 1, 5, 5, Vector3::UNIT_Z);
	Entity *entGround = mSceneMgr->createEntity("GroundEntity", "ground");
    mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);
	
	entGround->setMaterialName("Examples/Rockwall");
	entGround->setCastShadows(false);
	
	// create a timer that causes OGRE to render at 50fps
	//[NSTimer scheduledTimerWithTimeInterval:0.02 target:self selector:@selector(renderFrame) userInfo:NULL repeats:YES];
}

void BaseFramework::destroyScene() {}
