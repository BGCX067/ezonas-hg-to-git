#pragma once

#define SGLT_CAM Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW Application :: getSingletonPtr() -> GetRW()

#define FOR(I) for(int i = 0; i < I; ++i)
//#define USE_TERRAIN
// Ogre
#include "Ogre\Ogre.h"
#include "OIS\OIS.h"
//#include "Ogre\Terrain\OgreTerrain.h"
using namespace std;
using namespace Ogre;
using namespace OIS;

typedef Ogre :: Vector3 Vec3;

// Project

#define OG_SGLT Ogre::Singleton

#include "ConfMgr.h"
#include "BulletTracer.h"
#include "LaserCast.h"
#include "FPersonCam.h"
#include "Application.h"

