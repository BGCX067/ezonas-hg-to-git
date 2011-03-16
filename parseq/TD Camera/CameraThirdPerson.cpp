
#include "CameraThirdPerson.h"

CameraThirdPerson::CameraThirdPerson()
{
}

CameraThirdPerson::CameraThirdPerson(Camera& _Cam)
: Camera(_Cam)
{
}

CameraThirdPerson::~CameraThirdPerson()
{	
}

void CameraThirdPerson::walk(float units)
{
}

void CameraThirdPerson::strafe(float units)
{
}

void CameraThirdPerson::fly(float units)
{
}

void CameraThirdPerson::yaw(float angle)
{
	D3DXMATRIX T;

	//D3DXMatrixRotationAxis(&T, &_up, angle);
	// rotate around world y (0, 1, 0) also for ThirdPerson cam
	D3DXMatrixRotationY(&T, angle);

	// rotate _right and _look around _up or y-axis
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}

void CameraThirdPerson::roll(float angle)
{
	// only roll for aircraft type
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_look,	angle);

	// rotate _up and _right around _look vector
	D3DXVec3TransformCoord(&_right,&_right, &T);
	D3DXVec3TransformCoord(&_up,&_up, &T);
}


void CameraThirdPerson::update(float timeDelta)
{
	//
	// Update: Update the CameraThirdPerson.
	//

	// Get target orientation
	if (m_pTarget)
	{	
		D3DXVECTOR3 vUp(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 vTargetPos, vTargetAtXZ, vOffset; 

		m_pTarget->GetPos(&vTargetPos);
		m_pTarget->GetLook(&vTargetAtXZ);
		vTargetAtXZ.y = 0.0f;
		D3DXVec3Normalize(&vTargetAtXZ, &vTargetAtXZ);
		
		vOffset = m_fBack * vTargetAtXZ - m_fHeight * vUp;
		_pos = vTargetPos - vOffset;

		D3DXVec3Normalize(&_look, &vOffset);

		D3DXVec3Cross(&_right, &vUp, &_look);
		D3DXVec3Normalize(&_right, &_right);
	
		D3DXVec3Cross(&_up, &_look, &_right);
		D3DXVec3Normalize(&_up, &_up);
	}

	if( ::GetAsyncKeyState('A') & 0x8000f )
		strafe(-4.0f * timeDelta);

	if( ::GetAsyncKeyState('D') & 0x8000f )
		strafe(4.0f * timeDelta);
}

void CameraThirdPerson::setTarget(Object* _target)
{
	m_pTarget = _target;
}

void CameraThirdPerson::setOffset(float _fBack, float _fHeight)
{
	m_fBack = _fBack;
	m_fHeight = _fHeight;
}