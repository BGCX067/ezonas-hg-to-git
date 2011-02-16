
#include "CameraFirstPerson.h"

CameraFirstPerson::CameraFirstPerson()
{
}

CameraFirstPerson::CameraFirstPerson(Camera& _Cam)
: Camera(_Cam)
{
}

CameraFirstPerson::~CameraFirstPerson()
{

}

void CameraFirstPerson::walk(float units)
{
	// move only on xz plane for land object
	_pos += D3DXVECTOR3(_look.x, 0.0f, _look.z) * units;
}

void CameraFirstPerson::strafe(float units)
{
	// move only on xz plane for land object
	_pos += D3DXVECTOR3(_right.x, 0.0f, _right.z) * units;

}

void CameraFirstPerson::fly(float units)
{
	// move only on y-axis for land object
	_pos.y += units;
}

void CameraFirstPerson::yaw(float angle)
{
	D3DXMATRIX T;

	// rotate around world y (0, 1, 0) always for land object
	D3DXMatrixRotationY(&T, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
	D3DXVec3TransformCoord(&_up,&_up, &T);
}

void CameraFirstPerson::roll(float angle)
{
	// no roll
}


void CameraFirstPerson::update(float timeDelta)
{
	//
	// Update: Update the CameraFirstPerson.
	//
	_pos.y = 5.0f;

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