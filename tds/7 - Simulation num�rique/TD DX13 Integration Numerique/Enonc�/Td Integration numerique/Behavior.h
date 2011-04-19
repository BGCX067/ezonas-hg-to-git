/**
 * Behaviour.h
 * 
 * @author  Fabsther
 * @since   21/06/2010
 * @version 1.0
 */

#ifndef BEHAVIOR__H
#define BEHAVIOR__H

#include <d3dx9.h>

class Behavior
{
	protected : 

		D3DXVECTOR3 m_vForce;
		D3DXVECTOR3 m_vAcceleration;
		D3DXVECTOR3 m_vVelocity;
		D3DXVECTOR3 m_vPosition;
		float m_fMass;

	public : 

		Behavior();
		~Behavior();

		//accesseurs
		void SetForces( D3DXVECTOR3 _vForce );
		void AddForces( D3DXVECTOR3 _vForce );
		void ResetForces();
		void SetAcceleration( D3DXVECTOR3 _vAcceleration );
		void AddAcceleration( D3DXVECTOR3 _vAcceleration );
		void ResetAcceleration();
		void SetVelocity( D3DXVECTOR3 _vVelocity );
		void AddVelocity( D3DXVECTOR3 _vVelocity );
		void ResetVelocity();
		void SetPosition( D3DXVECTOR3 _vPosition );
		void AddPosition( D3DXVECTOR3 _vPosition );
		void ResetPosition();
		virtual void Update( float _fTimeDelta );
		D3DXVECTOR3 GetForce();
		D3DXVECTOR3 GetAcceleration();
		D3DXVECTOR3 GetVelocity();
		D3DXVECTOR3 GetPosition();


};

#endif //BEHAVIOR__H