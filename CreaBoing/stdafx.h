#pragma once

#include "Ogre\Ogre.h"
#include "OIS\OIS.h"
//#include "Ogre\Terrain\OgreTerrain.h"
//#define PHYSICS
#define CREABOING
using namespace std;
using namespace Ogre;
using namespace OIS;

typedef Ogre :: Vector3 Vec3;

// Project
#define FOR(I) for(int i = 0; i < I; ++i)

#define SGLT_APP Application :: getSingletonPtr()
#define SGLT_CAM Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW Application :: getSingletonPtr() -> GetRW()

#define OG_SGLT Ogre::Singleton

//#include "tinystr.h"
//#include "tinyxml.h"

//#include "DotSceneLoader.h"

#include "Gorilla.h"
#include "ConfMgr.h"
#include "CameraController.h"
//#include "Cam3rdperson.h"
#include "Application.h"

