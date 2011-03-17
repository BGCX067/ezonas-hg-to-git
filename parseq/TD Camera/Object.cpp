#include "Object.h"

Object::Object()
{
	m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;
	m_right.x = 1.0f;
	m_right.y = 0.0f;
	m_right.z = 0.0f;
	m_up.x = 0.0f;
	m_up.y = 1.0f;
	m_up.z = 0.0f;
	m_look.x = 0.0f;
	m_look.y = 0.0f;
	m_look.z = 1.0f;
}
Object::~Object()
{	
}
bool Object::Display(IDirect3DDevice9* Device, float timeDelta)
{
	D3DXMATRIX yRot, scale, identity, translation, turnShip;
	D3DXMatrixIdentity(&identity);

	// automatic rotation
	static float y = 0.0f;
	D3DXMatrixRotationY(&yRot, y);
	//y += timeDelta;
	if( y >= 6.28f )
		y = 0.0f;

	// Keep camera's axes orthogonal to each other
	D3DXVec3Normalize(&m_look, &m_look);

	D3DXVec3Cross(&m_up, &m_look, &m_right);
	D3DXVec3Normalize(&m_up, &m_up);

	D3DXVec3Cross(&m_right, &m_up, &m_look);
	D3DXVec3Normalize(&m_right, &m_right);

	// Build the view matrix:
	(yRot)(0,0) = m_right.x; (yRot)(1, 0) = m_up.x; (yRot)(2, 0) = m_look.x; (yRot)(3, 0) = 0.0f;
	(yRot)(0,1) = m_right.y; (yRot)(1, 1) = m_up.y; (yRot)(2, 1) = m_look.y; (yRot)(3, 1) = 0.0f;
	(yRot)(0,2) = m_right.z; (yRot)(1, 2) = m_up.z; (yRot)(2, 2) = m_look.z; (yRot)(3, 2) = 0.0f;
	(yRot)(0,3) = 0.0f;	  (yRot)(1, 3) = 0.0f;   (yRot)(2, 3) = 0.0f;	 (yRot)(3, 3) = 1.0f;

	// Scale Object
	D3DXMatrixScaling(&scale, 0.5f, 0.5f, 0.5f);
	D3DXMatrixMultiply(&World, &identity, &scale);

	// Turn 180 degrees around Up axis to fix ship orientation
	D3DXMatrixRotationAxis(&turnShip, &m_up, 3.14f);
	D3DXMatrixMultiply(&World, &turnShip, &World);

	// Apply the rotation matrix to world
	D3DXMatrixMultiply(&World, &yRot, &World);

	// Translate to position
	D3DXMatrixTranslation(&translation, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&World, &World, &translation);	


	Device->SetTransform(D3DTS_WORLD, &World);


	return true;
}
void Object::GetMatrix (D3DXMATRIX* _m)
{
   *_m = World;
}
void Object::GetLook (D3DXVECTOR3* _look)
{
   *_look = m_look;
}
void Object::GetPos (D3DXVECTOR3* _pos)
{
   *_pos = m_pos;
}
void Object::GetUp (D3DXVECTOR3* _up)
{
   *_up = m_up;
}
void Object::Update(float timeDelta)
{	
}