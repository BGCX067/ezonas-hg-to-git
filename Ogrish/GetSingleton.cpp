#include "stdafx.h"

Application * Application :: getSingletonPtr(void)		{ return ms_Singleton; }
ConfMgr * ConfMgr :: getSingletonPtr(void)				{return ms_Singleton; }
LaserCast * LaserCast :: getSingletonPtr(void)			{ return ms_Singleton; }
FPersonCam * FPersonCam :: getSingletonPtr(void)		{ return ms_Singleton; }
BulletTracer * BulletTracer :: getSingletonPtr(void)	{ return ms_Singleton; }

Application * Application :: Instantiate(void)		{ new Application; return ms_Singleton; }
ConfMgr * ConfMgr :: Instantiate(void)				{ new ConfMgr; return ms_Singleton; }
LaserCast * LaserCast :: Instantiate(void)			{ new LaserCast; return ms_Singleton; }
FPersonCam * FPersonCam :: Instantiate(void)		{ new FPersonCam; return ms_Singleton; }
BulletTracer * BulletTracer :: Instantiate(void)	{ new BulletTracer; return ms_Singleton; }
