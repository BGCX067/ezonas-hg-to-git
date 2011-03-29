// OBB.cpp: implementation of the OBB class.
//
//////////////////////////////////////////////////////////////////////

#include "OBB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

OBB::OBB(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh)
{
	m_pD3DDevice = pD3DDevice;

	D3DXCreateBox(
		m_pD3DDevice,
		5,
		20,
		10,
		&m_pBoxMesh,
		0);
}

OBB::~OBB()
{
}

void OBB::Update(D3DXMATRIX& _mWorld)
{
}

void OBB::Render()
{
	m_pBoxMesh->DrawSubset(0);
}