/**
 * Behaviour.h
 * 
 * @author  Fabsther
 * @since   21/06/2010
 * @version 1.0
 */

#ifndef BEHAVIOUR__H
#define BEHAVIOUR__H

#include <d3dx9.h>

class Behaviour
{
	protected : 

		D3DXVECTOR3 m_vForce;
		D3DXVECTOR3 m_vAcceleration;
		D3DXVECTOR3 m_vVelocity;
		D3DXVECTOR3 m_vPosition;
		float m_fMass;

	public : 

		Behaviour();
		~Behaviour();

		//accesseurs


};

#endif //BEHAVIOUR__H