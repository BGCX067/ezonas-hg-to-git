// BoundingSphere.h: interface for the BoundingSphere class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __BOUNDINGSPHERE_H__
#define __BOUNDINGSPHERE_H__

#include "d3dx9.h"

class BoundingSphere
{
public:
	BoundingSphere(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh);
	virtual ~BoundingSphere();

	float		getRadius() { return m_fRadius; }
	D3DXVECTOR3 getCenter() { return m_vCenter; }

    void Update(D3DXMATRIX& _mWorld);
	void Render();
	float m_fRadius;
	D3DXVECTOR3 m_vCenter;

private:
	ID3DXMesh* m_pSphereMesh;
	LPDIRECT3DDEVICE9 m_pD3DDevice;

	bool ComputeBoundingSphere(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride);
};

#endif // __BOUNDINGSPHERE_H__
