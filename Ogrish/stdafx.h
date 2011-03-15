#pragma once

#define FOR(I) for(int i = 0; i < I; ++i)
//#define USE_TERRAIN
// Ogre
#include "Ogre\Ogre.h"
#include "OIS\OIS.h"
#include "Ogre\Terrain\OgreTerrain.h"
using namespace std;
using namespace Ogre;
using namespace OIS;

typedef Ogre :: Vector3 Vec3;

// Project

#include "ConfMgr.h"
#include "BulletTracer.h"
#include "LaserCast.h"
#include "1stPersonCam.h"
#include "Application.h"

