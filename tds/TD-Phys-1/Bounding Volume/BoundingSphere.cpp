// BoundingSphere.cpp: implementation of the OBB class.
//
//////////////////////////////////////////////////////////////////////

#include "BoundingSphere.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#include "Game.h"

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

	mesh = Game :: GetSingleton() -> getMesh() -> GetMesh();
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

float BoundingSphere :: ComputeBoundingSphere()
{
	float result = 0.0f;

}
D3DXVECTOR3 BoundingSphere :: ComputeGravCenter()
{
	D3DXVECTOR3 result(0,0,0);
	int num = mesh -> GetNumVertices();
//	IDirect3DVertexBuffer9 * vertexBuffer;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;
	//LPDIRECT3DVERTEXBUFFER9;
	mesh -> GetVertexBuffer((*vertexBuffer));
	void* rawData;
	vertexBuffer -> Lock(0, mesh->GetNumBytesPerVertex() * mesh->GetNumVertices(), &rawData, D3DLOCK_READONLY);
	D3DVERTEXELEMENT9 decl;//[MAXD3DDECLLENGTH];
	UINT numElements;
	//mesh ->GetDeclaration();
	mesh -> GetDeclaration();
		decl.get
	mesh -> GetFVF();
	FOR(num)
	{

		result.x += (D3DXVECTOR3)rawData
		result.y += mesh ->
		result.z += mesh ->
	}
	vertexBuffer -> Unlock();
}