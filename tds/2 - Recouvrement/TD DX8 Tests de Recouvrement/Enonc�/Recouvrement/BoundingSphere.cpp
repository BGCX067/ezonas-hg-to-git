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

	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);

    hr = ComputeBoundingSphere(
			(D3DXVECTOR3*)v,
			mesh->GetNumVertices(),
			D3DXGetFVFVertexSize(mesh->GetFVF()));

	mesh->UnlockVertexBuffer();

    D3DXCreateSphere(
		m_pD3DDevice,
		getRadius(),
		20,
		20,
		&m_pSphereMesh,
		0);

}

BoundingSphere::~BoundingSphere()
{
}

bool BoundingSphere::ComputeBoundingSphere(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride)
{
    // find center

    D3DXVECTOR3 vmin(_vects->x,_vects->y,_vects->z);
    D3DXVECTOR3 vmax(vmin);

    BYTE *ptr = (BYTE*)_vects;
    ptr += _stride;
    for (int i=1;i<(int) _count;i++) 
    {
        D3DXVECTOR3 v = *((LPD3DXVECTOR3) ptr);
        if (v.x < vmin.x) vmin.x = v.x;
        if (v.y < vmin.y) vmin.y = v.y;
        if (v.z < vmin.z) vmin.z = v.z;
        if (v.x > vmax.x) vmax.x = v.x;
        if (v.y > vmax.y) vmax.y = v.y;
        if (v.z > vmax.z) vmax.z = v.z;
        ptr += _stride;
    }
	
	m_vCenter = D3DXVECTOR3((vmax.x + vmin.x)/2.0f,(vmax.y + vmin.y)/2.0f,(vmax.z + vmin.z)/2.0f);


    // find farthest point in set
    D3DXVECTOR3 v;
    m_fRadius=0.0f;

    ptr = (BYTE*)_vects;
    for (int i=0;i<(int) _count;i++) 
    {
        v = *((LPD3DXVECTOR3) ptr) - m_vCenter;
        float distSq = D3DXVec3LengthSq(&v);
        if (distSq > m_fRadius)
        {
            m_fRadius = distSq;
        }
        ptr += _stride;

    }

    m_fRadius = sqrtf(m_fRadius);

    return 0;
}

void BoundingSphere::Update(D3DXMATRIX& _mWorld)
{
    D3DXMATRIXA16  mat;
    D3DXMatrixTranslation(&mat, m_vCenter.x, m_vCenter.y, m_vCenter.z);
    D3DXMatrixMultiply(&mat, &mat, &_mWorld);
    m_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
}

void BoundingSphere::Render()
{
	m_pSphereMesh->DrawSubset(0);
}