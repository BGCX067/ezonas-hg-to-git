#ifndef __CameraFirstPersonH__
#define __CameraFirstPersonH__

#include "camera.h"

class CameraFirstPerson : public Camera
{
public:

	CameraFirstPerson();
    CameraFirstPerson(Camera& _Cam);
	~CameraFirstPerson();

    void update(float timeDelta);
    
	void strafe(float units);
	void fly(float units);  
	void walk(float units);  
	
	void yaw(float angle);   
	void roll(float angle);  

private:
};
#endif // __CameraFirstPersonH__