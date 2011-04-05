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

	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

    hr = ComputeOBoundingBox(
			(D3DXVECTOR3*)v,
			mesh->GetNumVertices(),
			D3DXGetFVFVertexSize(mesh->GetFVF()));

	mesh->UnlockVertexBuffer();

	D3DXCreateBox(
		m_pD3DDevice,
		m_fWidth,
		m_fHeight,
		m_fDepth,
		&m_pBoxMesh,
		0);
}

OBB::~OBB()
{
}

void OBB::Update(D3DXMATRIX& _mWorld)
{
    D3DXMatrixTranslation(&m_mWorld, m_vCenter.x, m_vCenter.y, m_vCenter.z);
    D3DXMatrixMultiply(&m_mWorld, &m_mWorld, &_mWorld);
    m_pD3DDevice->SetTransform(D3DTS_WORLD, &m_mWorld);    
}

void OBB::Render()
{
	m_pBoxMesh->DrawSubset(0);
}

bool OBB::ComputeOBoundingBox(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride)
{
    BYTE *ptr = (BYTE*)_vects;
    for (int i=0;i<(int) _count;i++) 
    {
        D3DXVECTOR3 v = *((LPD3DXVECTOR3) ptr);
		if (i==0)
		{
			m_min = v;
			m_max = m_min;
		}
        if (v.x < m_min.x)
            m_min.x = v.x;
        if (v.y < m_min.y)
            m_min.y = v.y;
        if (v.z < m_min.z)
            m_min.z = v.z;
        if (v.x > m_max.x)
            m_max.x = v.x;
        if (v.y > m_max.y)
            m_max.y = v.y;
        if (v.z > m_max.z)
            m_max.z = v.z;

        ptr += _stride;
    }

    m_fWidth = abs(m_max.x - m_min.x);
	m_fHeight = abs(m_max.y - m_min.y);
	m_fDepth = abs(m_max.z - m_min.z);

    //find center
    m_vCenter.x = (m_max.x + m_min.x)/2.0f;
	m_vCenter.y = (m_max.y + m_min.y)/2.0f;
	m_vCenter.z = (m_max.z + m_min.z)/2.0f;

    return 0;
}