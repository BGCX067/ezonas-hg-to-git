#pragma once

#define SGLT_CAM Application :: sglt() -> GetCam()
#define SGLT_RSN Application :: sglt() -> GetRSN()
#define SGLT_SCMGR Application :: sglt() -> GetScMgr()
#define SGLT_RW Application :: sglt() -> GetRW()

#define FOR(I) for(int i = 0; i < I; ++i)
//#define USE_TERRAIN
// Ogre
#include "Ogre\Ogre.h"
//#include "OIS\OIS.h"
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
#include "1stPersonCam.h"
#include "Application.h"

