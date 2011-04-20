/**
 * Behavior.cpp
 * 
 * @author  Fabsther
 * @since   21/06/2010
 * @version 1.0
 */

#include"Behavior.h"

Behavior::Behavior()
{
	m_vForce.x = 0.0f;
	m_vForce.y = 0.0f;
	m_vForce.z = 0.0f;
	m_vAcceleration.x = 0.0f;
	m_vAcceleration.y = 0.0f;
	m_vAcceleration.z = 0.0f;
	m_vVelocity.x = 0.0f;
	m_vVelocity.y = 0.0f;
	m_vVelocity.z = 0.0f;
	m_vPosition.x = 0.0f;
	m_vPosition.y = 0.0f;
	m_vPosition.z = 0.0f;
}

Behavior::~Behavior()
{
}

void Behavior::SetForces(D3DXVECTOR3 _vForce)
{
	m_vForce = _vForce;
}

void Behavior::AddForces(D3DXVECTOR3 _vForce)
{
	m_vForce.x += _vForce.x;
	m_vForce.y += _vForce.y;
	m_vForce.z += _vForce.z;
}

void Behavior::ResetForces()
{
	m_vForce.x = 0.0f;
	m_vForce.y = 0.0f;
	m_vForce.z = 0.0f;
}

void Behavior::SetAcceleration(D3DXVECTOR3 _vAcceleration){m_vAcceleration = _vAcceleration;}

void Behavior::AddAcceleration(D3DXVECTOR3 _vAcceleration)
{
	m_vAcceleration.x += _vAcceleration.x;
	m_vAcceleration.y += _vAcceleration.y;
	m_vAcceleration.z += _vAcceleration.z;
}

void Behavior::ResetAcceleration()
{
	m_vAcceleration.x = 0.0f;
	m_vAcceleration.y = 0.0f;
	m_vAcceleration.z = 0.0f;
}

void Behavior::SetVelocity(D3DXVECTOR3 _vVelocity){m_vVelocity = _vVelocity;}

void Behavior::AddVelocity(D3DXVECTOR3 _vVelocity)
{
	m_vVelocity.x += _vVelocity.x;
	m_vVelocity.y += _vVelocity.y;
	m_vVelocity.z += _vVelocity.z;
}

void Behavior::ResetVelocity()
{
	m_vVelocity.x = 0.0f;
	m_vVelocity.y = 0.0f;
	m_vVelocity.z = 0.0f;
}

void Behavior::SetPosition(D3DXVECTOR3 _vPosition){m_vPosition = _vPosition;}

void Behavior::AddPosition(D3DXVECTOR3 _vPosition)
{
	m_vPosition.x += _vPosition.x;
	m_vPosition.y += _vPosition.y;
	m_vPosition.z += _vPosition.z;
}

void Behavior::ResetPosition()
{
	m_vPosition.x = 0.0f;
	m_vPosition.y = 0.0f;
	m_vPosition.z = 0.0f;
}

D3DXVECTOR3 Behavior::GetForce(){return m_vForce;}
D3DXVECTOR3 Behavior::GetAcceleration(){return m_vAcceleration;}
D3DXVECTOR3 Behavior::GetVelocity(){return m_vVelocity;}
D3DXVECTOR3 Behavior::GetPosition(){return m_vPosition;}

void Behavior::Update(float _fTimeDelta)
{
}
