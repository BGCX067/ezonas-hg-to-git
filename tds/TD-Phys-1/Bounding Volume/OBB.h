// OBB.h: interface for the Axis Aligned Bounding box class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __OBB_H__
#define __OBB_H__

#include "d3dx9.h"

class OBB
{
public:
	OBB(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh);
	virtual ~OBB();

	D3DXVECTOR3 getMin() { return m_min; }
	D3DXVECTOR3 getMax() { return m_max; }

	bool ComputeOBoundingBox(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride);

	void Update(D3DXMATRIX& _mWorld);
	void Render();

private:
	ID3DXMesh* m_pBoxMesh;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	float m_fWidth;
	float m_fHeight;
	float m_fDepth;

    D3DXVECTOR3 m_min;
    D3DXVECTOR3 m_max;

	D3DXMATRIXA16	m_mWorld;
	D3DXVECTOR3		m_vCenter;
};

#endif // __OBB_H__
