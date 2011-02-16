#ifndef __CameraThirdPersonH__
#define __CameraThirdPersonH__

#include "camera.h"
#include "object.h"

class CameraThirdPerson : public Camera
{
public:

	CameraThirdPerson();
	CameraThirdPerson(Camera& _Cam);
	~CameraThirdPerson();

	void update(float timeDelta);

	void setTarget(Object* _target);
	void setOffset(float _fBack, float _fHeight);
	
	void strafe(float units);
	void fly(float units);	
	void walk(float units);  
	
	void yaw(float angle);  
	void roll(float angle); 

private:
	Object*	 m_pTarget;
	float	   m_fBack;
	float	   m_fHeight;
};
#endif // __CameraThirdPersonH__