// BoundingSphere.cpp: implementation of the OBB class.
//
//////////////////////////////////////////////////////////////////////

#include "BoundingSphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


BoundingSphere::BoundingSphere(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh)
{
	m_pD3DDevice = pD3DDevice;

    D3DXCreateSphere(
		m_pD3DDevice,
		5,
		20,
		20,
		&m_pSphereMesh,
		0);

}

BoundingSphere::~BoundingSphere()
{
}

void BoundingSphere::Update(D3DXMATRIX& _mWorld)
{
}

void BoundingSphere::Render()
{
	m_pSphereMesh->DrawSubset(0);
}