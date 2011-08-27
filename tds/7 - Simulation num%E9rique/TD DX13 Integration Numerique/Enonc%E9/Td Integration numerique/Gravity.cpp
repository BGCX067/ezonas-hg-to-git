/**
 * Gravity.cpp
 * 
 * @author  Fabsther
 * @since   21/06/2010
 * @version 1.0
 */

#include"Gravity.h"

Gravity::Gravity(D3DXVECTOR3* _vPosition, D3DXVECTOR3* _vVelocity)
{
	m_vPosition = *_vPosition;
	m_vVelocity = *_vVelocity;
	m_vInitPosition = *_vPosition;
	m_vInitVelocity = *_vVelocity;
	m_vGravity = D3DXVECTOR3 (0.0f, -9.81f, 0.0f);
	m_fTime = 0.0f;
}

void Gravity::Update( float _fTimeDelta )
{
	m_fTime += _fTimeDelta;
	m_vVelocity += 0.5f * m_vGravity * _fTimeDelta;
	m_vPosition += m_vVelocity * _fTimeDelta;

	if (m_vPosition.y < 5.0f)
	{
		m_vPosition.y = 5.0f;
		m_vVelocity.y = fabs (m_vVelocity.y * 0.6f);
	}
}
