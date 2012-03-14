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

#include <cmath>
//#define LASERCAST
typedef Ogre::Vector3 Vec3;
typedef Ogre::Vector2 Vec2;
#include "Procedural.h"

#include <OgreTextAreaOverlayElement.h>

// Bullet Physics include files
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include "BtOgreExtras.h"
#include "BtOgrePG.h"
#include "BtOgreGP.h"


// Gorilla and console
#include "Gorilla.h"
#include "OgreConsoleForGorilla.h"
using namespace std;
using namespace Ogre;

#include "defines.h"

// dirty, but necessary
struct Application;
extern Application * appli;

#include "fx_LaserCast.h"

#include "game_datastruct.h"
#include "game_items.h"
#include "game_ability.h"
#include "game_character.h"
#include "game_gamemachine.h"

#include "eff_bullets.h"
#include "Application.h"


