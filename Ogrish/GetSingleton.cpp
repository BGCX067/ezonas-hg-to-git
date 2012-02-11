#ifdef FUCKSHIT
#include "stdafx.h"
//#endif
Application * Application :: getSingletonPtr(void)				{ return ms_Singleton; }
LaserCast * LaserCast :: getSingletonPtr(void)					{ return ms_Singleton; }
CameraController * CameraController :: getSingletonPtr(void)	{ return ms_Singleton; }
BulletTracer * BulletTracer :: getSingletonPtr(void)			{ return ms_Singleton; }
//Cam3rdperson * Cam3rdperson :: getSingletonPtr(void)			{ return ms_Singleton; }

Application * Application :: Instantiate(void)				{ new Application; return ms_Singleton; }
LaserCast * LaserCast :: Instantiate(void)					{ new LaserCast; return ms_Singleton; }
CameraController * CameraController :: Instantiate(void)	{ new CameraController; return ms_Singleton; }
BulletTracer * BulletTracer :: Instantiate(void)			{ new BulletTracer; return ms_Singleton; }
//Cam3rdperson * Cam3rdperson :: Instantiate(void)			{ new Cam3rdperson; return ms_Singleton; }
#endif