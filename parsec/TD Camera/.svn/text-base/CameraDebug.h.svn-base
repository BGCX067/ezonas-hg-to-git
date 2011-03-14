#ifndef __CameraDebugH__
#define __CameraDebugH__

#include "camera.h"

class CameraDebug : public Camera
{
public:

	CameraDebug();
	CameraDebug(Camera& _Cam);
	~CameraDebug();

    void update(float timeDelta);
    
	void strafe(float units);
	void fly(float units);    
	void walk(float units);  
	
	void yaw(float angle);  
	void roll(float angle); 

private:
};
#endif // __CameraDebugH__