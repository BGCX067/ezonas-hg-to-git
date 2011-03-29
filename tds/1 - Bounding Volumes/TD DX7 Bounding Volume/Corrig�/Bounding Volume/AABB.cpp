// AABB.cpp: implementation of the AABB class.
//
//////////////////////////////////////////////////////////////////////

#include "AABB.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


AABB::AABB(LPDIRECT3DDEVICE9 pD3DDevice, ID3DXMesh* mesh)
: CCuboid(pD3DDevice)
{
	HRESULT hr = 0;

	BYTE* v = 0;
	mesh->LockVertexBuffer(0, (void**)&v);


    // TD BOUNDING VOLUME Q2: Calcul des parametres de la bounding box
    hr = ComputeAABoundingBox(
			(D3DXVECTOR3*)v,
			mesh->GetNumVertices(),
			D3DXGetFVFVertexSize(mesh->GetFVF()));

	mesh->UnlockVertexBuffer();

    m_rWidth = abs(max.x - min.x);
	m_rHeight = abs(max.y - min.y);
	m_rDepth = abs(max.z - min.z);

	//Initialize Vertex Buffer
    if(SUCCEEDED(CreateVertexBuffer()))
	{
		if(CreateIndexBuffer())
		{
			UpdateVertices();
		}
	}
}

AABB::~AABB()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pVertexBuffer);
}

bool AABB::UpdateVertices()
{
	VOID* pVertices;
	CUBOID_CUSTOMVERTEX cvVertices[] =
	{	
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 0
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 1
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 2
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},	    //Vertex 3
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},	    //Vertex 4
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 5
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 6
        {m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.1f,},		//Vertex 7
	};

	// Only for AABB, replace the vertices with the OBB in the world
    for (int i=0; i<8; i++)
    {        
        cvVertices[i].x = m_pworld[i].x;
        cvVertices[i].y = m_pworld[i].y;
        cvVertices[i].z = m_pworld[i].z;
    }

    // Compute normals for each Vertex from surrounding vertices
    ComputeVertexNormal(cvVertices, 0, 1, 2, 4);
    ComputeVertexNormal(cvVertices, 1, 0, 7, 3);
    ComputeVertexNormal(cvVertices, 2, 0, 3, 5);
    ComputeVertexNormal(cvVertices, 3, 0, 6, 5);
    ComputeVertexNormal(cvVertices, 4, 0, 5, 7);
    ComputeVertexNormal(cvVertices, 5, 4, 2, 6);

	//Get a pointer to the vertex buffer vertices and lock the vertex buffer
    if(FAILED(m_pVertexBuffer->Lock(0, sizeof(cvVertices), (void**)&pVertices, 0)))
    {
        return false;
    }

    //Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, cvVertices, sizeof(cvVertices));

    //Unlock the vertex buffer
    m_pVertexBuffer->Unlock();


	return true;
}

void AABB::Update(D3DXMATRIX& _World)
{
    for (int i=0; i<8; i++)
    {
        D3DXVec3TransformCoord(&m_pworld[i], &m_pobject[i], &_World);
    }
	ComputeAABBFromOBB();
    UpdateVertices();
}

bool AABB::ComputeAABoundingBox(D3DXVECTOR3* _vects,DWORD _count,DWORD _stride)
{
    min = D3DXVECTOR3(_vects->x,_vects->y,_vects->z);
    max = min;

    BYTE *ptr = (BYTE*)_vects;
    ptr += _stride;
    for (int i=1;i<(int) _count;i++) 
    {
        D3DXVECTOR3 v = *((LPD3DXVECTOR3) ptr);
        if (v.x < min.x)
            min.x = v.x;
        if (v.y < min.y)
            min.y = v.y;
        if (v.z < min.z)
            min.z = v.z;
        if (v.x > max.x)
            max.x = v.x;
        if (v.y > max.y)
            max.y = v.y;
        if (v.z > max.z)
            max.z = v.z;
        ptr += _stride;
    }

    // Update points 
    m_pobject[0] = D3DXVECTOR3( min.x, max.y, min.z ); // xYz
    m_pobject[1] = D3DXVECTOR3( min.x, max.y, max.z ); // xYZ    
    m_pobject[2] = D3DXVECTOR3( max.x, max.y, min.z ); // XYz
    m_pobject[3] = D3DXVECTOR3( max.x, max.y, max.z ); // XYZ
    m_pobject[4] = D3DXVECTOR3( min.x, min.y, min.z ); // xyz
    m_pobject[5] = D3DXVECTOR3( max.x, min.y, min.z ); // Xyz
    m_pobject[6] = D3DXVECTOR3( max.x, min.y, max.z ); // XyZ
    m_pobject[7] = D3DXVECTOR3( min.x, min.y, max.z ); // xyZ
    return 0;
}

bool AABB::ComputeAABBFromOBB()
{
    // Find max and min points
    D3DXVECTOR3 min = m_pworld[0];
    D3DXVECTOR3 max = m_pworld[0];

    for (int i=1;i<8;i++) 
    {
        if (min.x > m_pworld[i].x)
            min.x = m_pworld[i].x;
        if (min.y > m_pworld[i].y)
            min.y = m_pworld[i].y;
        if (min.z > m_pworld[i].z)
            min.z = m_pworld[i].z;
        if (max.x < m_pworld[i].x)
            max.x = m_pworld[i].x;
        if (max.y < m_pworld[i].y)
            max.y = m_pworld[i].y;
        if (max.z < m_pworld[i].z)
            max.z = m_pworld[i].z;
    }

    // Update points 
    m_pworld[0] = D3DXVECTOR3( min.x, max.y, min.z ); // xYz
    m_pworld[1] = D3DXVECTOR3( min.x, max.y, max.z ); // xYZ    
    m_pworld[2] = D3DXVECTOR3( max.x, max.y, min.z ); // XYz
    m_pworld[3] = D3DXVECTOR3( max.x, max.y, max.z ); // XYZ
    m_pworld[4] = D3DXVECTOR3( min.x, min.y, min.z ); // xyz
    m_pworld[5] = D3DXVECTOR3( max.x, min.y, min.z ); // Xyz
    m_pworld[6] = D3DXVECTOR3( max.x, min.y, max.z ); // XyZ
    m_pworld[7] = D3DXVECTOR3( min.x, min.y, max.z ); // xyZ
    
    return true;
}