#pragma once

#include "Ogre.h"
#include "OIS/OIS.h"
//#include "Ogre\Terrain\OgreTerrain.h"

//#define PHYSICS
using namespace std;
using namespace Ogre;
using namespace OIS;

typedef Ogre :: Vector3 Vec3;
#define TO_STR StringConverter :: toString
// Project
#define FOR(I) for(int i = 0; i < I; ++i)

#define SGLT_APP Application :: getSingletonPtr()
#define SGLT_CAM Application :: getSingletonPtr() -> GetCam()
#define SGLT_RSN Application :: getSingletonPtr() -> GetRSN()
#define SGLT_SCMGR Application :: getSingletonPtr() -> GetScMgr()
#define SGLT_RW Application :: getSingletonPtr() -> GetRW()
//#define SGLT_CFG ConfMgr :: getSingletonPtr()

#define OG_SGLT Ogre::Singleton

#define PRINTLOG(s) LogManager::getSingleton().getDefaultLog()->logMessage(s)

//#include "tinystr.h"
//#include "tinyxml.h"
     #include <OgreTextAreaOverlayElement.h>

//#include "DotSceneLoader.h"
#ifdef PHYSICS
#include <btBulletDynamicsCommon.h>
#include "OgreMotionState.h"
#endif
//#define CCS_CODE
#ifdef CCS_CODE
#include "CCS\CCSFastDelegate.h"
#include "CCS\CCSFastDelegateBind.h"
#include "CCS\CCSCameraControlSystem.h"
#include "CCS\CCSPrerequisites.h"
#include "CCS\CCSBasicCameraModes.h"
#include "CCS\CCSFreeCameraMode.h"
#include "CCS\CCSOrbitalCameraMode.h"
#include "CCS\CCSCameraControlSystem.h"
#include "CCS\DummyCameraMode.h"
#endif


#include "datastruct.h"
#include "items.h"
#include "gamemachine.h"

#include "Gorilla.h"
#include "OgreConsoleForGorilla.h"


//#include "ConfMgr.h"
#include "BulletTracer.h"
#include "LaserCast.h"
#include "CameraController.h"
//#include "Cam3rdperson.h"
#include "Application.h"

