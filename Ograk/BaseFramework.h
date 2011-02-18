//
//  BaseFramework.h
//  OgreTest
//
//  Created by Penn Su on 2/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __BaseFramework_h_
#define __BaseFramework_h_

#import <Foundation/Foundation.h>
#import <Ogre/Ogre.h>

#import <Ogre/OgreTerrain.h>

#import <OIS/OISEvents.h>

using namespace Ogre;

class BaseFramework : public FrameListener {
public:
	BaseFramework();
	virtual ~BaseFramework();
	
	virtual void go();
	
protected:
	
	virtual bool setup();
	virtual void renderFrame();
	
	virtual void createScene();
	virtual void createViewports();
	virtual void createCamera();
	virtual void createFrameListens();
	
	// FrameListener
	virtual bool frameRenderingQueued(const FrameEvent& evt);
	
	// KeyListener
	
	// Memory management
	virtual void destroyScene();
	
	Root *mRoot;
	Camera *mCamera;
	SceneManager *mSceneMgr;
	RenderWindow *mWindow;
	SceneNode *objectNode;
	
	bool mShutDown;
	
};
	
#endif
