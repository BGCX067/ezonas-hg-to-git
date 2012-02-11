#pragma once
/*
 * This game use those following libraries/engines:
 * Bullet   - Physics Engine
 * Enet     - UDP networking library
 * Ogre3D   - 3d engine (opengl)
 * Gorilla  - 2D graphics interface for Ogre3D
 */

#include "Ogre.h"
//#include "Ogre\Terrain\OgreTerrain.h"
#include <OgreTextAreaOverlayElement.h>

#ifdef __APPLE__
#include <macUtils.h>
#define CROSSLOAD(s) load(macBundlePath() + "/Contents/Resources/"+s)
#include "OIS/OIS.h"
#else
#define CROSSLOAD(s) load(s)
#include "OIS.h"
#define PHYSICS
#endif

#ifdef PHYSICS
//#include <btBulletCollisionCommon.h>
#include <btBulletDynamicsCommon.h>
#include "BtOgrePG.h"
#include "BtOgreGP.h"
#include "BtOgreExtras.h"
//#include "OgreMotionState.h"
#endif

using namespace std;
//using namespace Ogre;
using namespace OIS;


#include "game_gamemachine.h"

#include "Gorilla.h"
#include "OgreConsoleForGorilla.h"

#include "fx_BulletTracer.h"
#include "fx_LaserCast.h"
#include "CameraController.h"

#include "game_datastruct.h"
#include "game_items.h"
#include "game_ability.h"
#include "game_character.h"

#include "Application.h"

#ifndef DEFINES

//typedef Ogre :: Vector3 Ogre::Vector3;
#define TO_STR(s) Ogre::StringConverter::toString(s)
#define FOR(I) for(size_t i = 0; i < I; ++i)
#define FOR_VECT(vect, type) for(std::vector<type>::iterator it = vect.begin(); it != vect.end(); ++it)
#define FOR_VECT2(vect, type) for(std::vector<type>::iterator it2 = vect.begin(); it2 != vect.end(); ++it2)

#define ITER_VECT(type) std::vector<type>::iterator

#define SGLT_APP		Application :: getSingletonPtr()
#define SGLT_CAM		Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN		Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR		Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW			Application :: getSingletonPtr() -> GetRW()
#define SGLT_LOG		Ogre::LogManager::getSingleton().getDefaultLog()
#define OG_SGLT			Ogre::Singleton

#define PRINTLOG(s) Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(s)

#define ITV(T)    std::vector	<T>::Iterator	
#define ITA(T)    std::array	<T>::Iterator	
#define ITQ(T)    std::queue	<T>::Iterator	
#define ITD(T)    std::deque	<T>::Iterator	
#define ITL(T)    std::list		<T>::Iterator	
#define ITM(T,U)  std::map		<T,U>::Iterator 
#define ITS(T)    std::stack	<T>::Iterator	

#endif
