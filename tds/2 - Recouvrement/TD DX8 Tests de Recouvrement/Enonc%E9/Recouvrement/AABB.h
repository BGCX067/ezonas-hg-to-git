// AABB.h: interface for the Oriented Bounding box class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AABB_H__
#define __AABB_H__

#include "cuboid.h"

class AABB : public CCuboid
{
public:
	AABB(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh);
	virtual ~AABB();

	void Update(D3DXMATRIX& _mWorld);
    D3DXVECTOR3 m_pobject[8];
    D3DXVECTOR3 m_pworld[8];
    D3DXVECTOR3 min;
    D3DXVECTOR3 max;

private:

	bool ComputeAABoundingBox(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride);
	bool ComputeAABBFromOBB();
	bool UpdateVertices();
};

#endif // __AABB_H__
