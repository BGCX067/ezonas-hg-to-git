#include "stdafx.h"

Application * Application :: getSingletonPtr(void)				{ return ms_Singleton; }
ConfMgr * ConfMgr :: getSingletonPtr(void)						{ return ms_Singleton; }
CameraController * CameraController :: getSingletonPtr(void)	{ return ms_Singleton; }
//Cam3rdperson * Cam3rdperson :: getSingletonPtr(void)			{ return ms_Singleton; }

Application * Application :: Instantiate(void)				{ new Application; return ms_Singleton; }
ConfMgr * ConfMgr :: Instantiate(void)						{ new ConfMgr; return ms_Singleton; }
CameraController * CameraController :: Instantiate(void)	{ new CameraController; return ms_Singleton; }
//Cam3rdperson * Cam3rdperson :: Instantiate(void)			{ new Cam3rdperson; return ms_Singleton; }