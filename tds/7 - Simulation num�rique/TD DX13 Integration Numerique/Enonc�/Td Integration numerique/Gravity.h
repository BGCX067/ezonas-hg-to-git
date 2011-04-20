/**
 * Gravity.h
 * 
 * @author  Fabsther
 * @since   21/06/2010
 * @version 1.0
 */


#ifndef GRAVITY__H
#define GRAVITY__H

#include"Behavior.h"
#include <d3dx9.h>

class Gravity : public Behavior
{
	protected:
	
		D3DXVECTOR3 m_vInitVelocity;
		D3DXVECTOR3 m_vInitPosition;
		D3DXVECTOR3 m_vGravity;
		float m_fTime;

	public :

		Gravity(D3DXVECTOR3* _vPosition, D3DXVECTOR3* _vVelocity);
		virtual void Update(float _fTimeDelta);
};

#endif //GRAVITY__H