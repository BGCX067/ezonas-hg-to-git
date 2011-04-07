
#include "Cameradebug.h"

CameraDebug::CameraDebug()
{
}

CameraDebug::CameraDebug(Camera& _Cam)
: Camera(_Cam)
{
}

CameraDebug::~CameraDebug()
{    
}

void CameraDebug::walk(float units)
{
	_pos += _look * units;
}

void CameraDebug::strafe(float units)
{
	_pos += _right * units;
}

void CameraDebug::fly(float units)
{
	_pos += _up * units;
}

void CameraDebug::yaw(float angle)
{
	D3DXMATRIX T;

	//D3DXMatrixRotationAxis(&T, &_up, angle);
	// rotate around world y (0, 1, 0) also for debug cam
	D3DXMatrixRotationY(&T, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void CameraDebug::roll(float angle)
{
	// only roll for aircraft type
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_look,	angle);

	// rotate _up and _right around _look vector
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_up,&_up, &T);
}


void CameraDebug::update(float timeDelta)
{
    //
	// Update: Update the CameraDebug.
	//

	if( ::GetAsyncKeyState('Z') & 0x8000f )
		walk(4.0f * timeDelta);

	if( ::GetAsyncKeyState('S') & 0x8000f )
		walk(-4.0f * timeDelta);

	if( ::GetAsyncKeyState('Q') & 0x8000f )
		strafe(-4.0f * timeDelta);

	if( ::GetAsyncKeyState('D') & 0x8000f )
		strafe(4.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_UP) & 0x8000f )
		pitch(-1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_DOWN) & 0x8000f )
		pitch(1.0f * timeDelta);

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f )
		yaw(-1.0f * timeDelta);
		
	if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f )
		yaw(1.0f * timeDelta);

}