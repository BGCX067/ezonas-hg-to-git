#pragma once
/*
 * This game use those following libraries/engines:
 * Bullet   - Physics Engine
 * Enet     - UDP networking library
 * Ogre3D   - 3d engine (opengl)
 * Gorilla  - 2D graphics interface for Ogre3D
 */


#ifdef __APPLE__
#include <macUtils.h>
#endif

#ifdef __APPLE__
#define CROSSLOAD(s) load(macBundlePath() + "/Contents/Resources/"+s)
#else
#define CROSSLOAD(s) load(s)
#endif

#include "Ogre.h"
#ifdef __APPLE__
#include "OIS/OIS.h"
#else
#include "OIS.h"
#endif
//#include "Ogre\Terrain\OgreTerrain.h"

//#define PHYSICS
using namespace std;
using namespace Ogre;
using namespace OIS;

typedef Ogre :: Vector3 Vec3;
#define TO_STR StringConverter :: toString
#define FOR(I) for(int i = 0; i < I; ++i)
#define FOR_VECT(vect, type) for(std::vector<type>::iterator it = vect.begin(); it != vect.end(); ++it)
#define FOR_VECT2(vect, type) for(std::vector<type>::iterator it2 = vect.begin(); it2 != vect.end(); ++it2)

#define ITER_VECT(type) std::vector<type>::iterator

#define SGLT_APP Application :: getSingletonPtr()
#define SGLT_CAM Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW Application :: getSingletonPtr() -> GetRW()

#define OG_SGLT Ogre::Singleton

#define PRINTLOG(s) LogManager::getSingleton().getDefaultLog()->logMessage(s)

//#include "tinystr.h"
//#include "tinyxml.h"
//#include "DotSceneLoader.h"
#include <OgreTextAreaOverlayElement.h>

#ifdef PHYSICS
#include <btBulletDynamicsCommon.h>
#include "OgreMotionState.h"
#endif

#include "datastruct.h"
#include "items.h"
#include "ability.h"
#include "character.h"

#include "gamemachine.h"

#include "Gorilla.h"
#include "OgreConsoleForGorilla.h"

#include "BulletTracer.h"
#include "LaserCast.h"
#include "CameraController.h"
#include "Application.h"

