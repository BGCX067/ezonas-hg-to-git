//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: camera.h
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Defines a camera's position and orientation.
//		 
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __cameraH__
#define __cameraH__

#include <d3dx9.h>
#include "object.h"

class Camera
{
public:
	Camera();
	Camera(Camera& _Cam);
	~Camera();

	virtual void update(float timeDelta);

	virtual void strafe(float units); // left/right
	virtual void fly(float units);	// up/down
	virtual void walk(float units);   // forward/backward
	
	virtual void pitch(float angle); // rotate on right vector
	virtual void yaw(float angle);   // rotate on up vector
	virtual void roll(float angle);  // rotate on look vector

	virtual void setTarget(Object* _target){};
	virtual void setOffset(float _fBack, float _fHeight){};

	void getViewMatrix(D3DXMATRIX* V); 
	void setViewMatrix(D3DXMATRIX* V); 
	void getPosition(D3DXVECTOR3* pos); 
	void setPosition(D3DXVECTOR3* pos); 

	void getRight(D3DXVECTOR3* right);
	void getUp(D3DXVECTOR3* up);
	void getLook(D3DXVECTOR3* look);
	
protected:
	D3DXVECTOR3 _right;
	D3DXVECTOR3 _up;
	D3DXVECTOR3 _look;
	D3DXVECTOR3 _pos;
};
#endif // __cameraH__