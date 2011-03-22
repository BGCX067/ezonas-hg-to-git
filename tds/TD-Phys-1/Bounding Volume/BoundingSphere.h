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

private:
	float m_fRadius;
	D3DXVECTOR3 m_vCenter;
	ID3DXMesh* m_pSphereMesh;
	LPDIRECT3DDEVICE9 m_pD3DDevice;
	float ComputeBoundingSphere();
	D3DXVECTOR3 ComputeGravCenter();
	ID3DXMesh * mesh;
};

#endif // (__BOUNDINGSPHERE_H__)
