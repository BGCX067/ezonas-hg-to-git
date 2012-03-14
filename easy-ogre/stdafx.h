#pragma once
/*
 * This game use those following libraries/engines:
 * Bullet   - Physics Engine
 * Enet     - UDP networking library
 * Ogre3D   - 3d engine (opengl)
 * Gorilla  - 2D graphics interface for Ogre3D
 */

//#include <boost/algorithm/string.hpp>
// Ogre3D & OIS include files

#include <Ogre.h>
#ifdef __APPLE__
#include <macUtils.h>
#include <OIS/OIS.h>
#define CROSSLOAD(s) load(macBundlePath() + "/Contents/Resources/"+s)
#else
#include <OIS.h>
#define CROSSLOAD(s) load(s)
#endif

#include "Procedural.h"
#define TO_STR StringConverter :: toString
#define NODE(s) scmgr->getRootSceneNode()->createChildSceneNode(s)
#define ENTITY scmgr->createEntity
#define LOGMSG(s) Ogre::LogManager::getSingleton().getDefaultLog()->logMessage(s)

using namespace std;
using namespace Ogre;

typedef Ogre::Vector3 Vec3;
typedef Ogre::Vector2 Vec2;




