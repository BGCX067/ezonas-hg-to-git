// Cuboid.cpp: implementation of the CCuboid class.
//
//////////////////////////////////////////////////////////////////////

#include "Cuboid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCuboid::CCuboid(LPDIRECT3DDEVICE9 pD3DDevice, float x, float y, float z)
{
	m_pD3DDevice = pD3DDevice;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pTexture = NULL;

	//Setup counts for this object
	m_dwNumOfVertices = 24;	
	m_dwNumOfIndices  = 36;
	m_dwNumOfPolygons = 12;

	//Set a default size and position
	m_rWidth = 10.0;
	m_rHeight = 10.0;
	m_rDepth = 10.0;
	m_rX = x;
	m_rY = y;
	m_rZ = z;

	//Set material default values (R, G, B, A)
	D3DCOLORVALUE rgbaDiffuse  = {1.0, 1.0, 1.0, 0.0,};
	D3DCOLORVALUE rgbaAmbient  = {1.0, 1.0, 1.0, 0.0,};
	D3DCOLORVALUE rgbaSpecular = {0.0, 0.0, 0.0, 0.0,};
	D3DCOLORVALUE rgbaEmissive = {0.0, 0.0, 0.0, 0.0,};
	
	SetMaterial(rgbaDiffuse, rgbaAmbient, rgbaSpecular, rgbaEmissive, 0);

	//Initialize Vertex Buffer
    if(SUCCEEDED(CreateVertexBuffer()))
	{
		if(CreateIndexBuffer())
		{
			UpdateVertices();
		}
	}
}

CCuboid::~CCuboid()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pVertexBuffer);
}

DWORD CCuboid::Render()
{
	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(CUBOID_CUSTOMVERTEX));
    m_pD3DDevice->SetFVF( CUBOID_D3DFVF_CUSTOMVERTEX );

	if(m_pTexture != NULL)
	{
		//A texture has been set. We want our texture to be shaded based
		//on the current light levels, so used D3DTOP_MODULATE.
		m_pD3DDevice->SetTexture(0, m_pTexture);
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	}
	else
	{
		//No texture has been set
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
		m_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_CURRENT);
	}

	//Select the material to use
	m_pD3DDevice->SetMaterial(&m_matMaterial);
	
	//Select index buffer
	m_pD3DDevice->SetIndices(m_pIndexBuffer);

	//Render polygons from index buffer
	m_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwNumOfVertices, 0, m_dwNumOfPolygons);

	//Return the number of polygons rendered
	return m_dwNumOfPolygons;
}

HRESULT CCuboid::CreateVertexBuffer()
{
    //Create the vertex buffer from our device.
    if(FAILED(m_pD3DDevice->CreateVertexBuffer(m_dwNumOfVertices * sizeof(CUBOID_CUSTOMVERTEX),
                                               0, CUBOID_D3DFVF_CUSTOMVERTEX,
                                               D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
    {
        return E_FAIL;
    }

    return S_OK;
}

bool CCuboid::CreateIndexBuffer()
{
	VOID* pBufferIndices;
	
	//Create the index buffer from our device
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(m_dwNumOfIndices * sizeof(WORD), 
											  0, D3DFMT_INDEX16, D3DPOOL_MANAGED,
											  &m_pIndexBuffer, NULL)))
	{
	    return false;
	}
	
	// TD2 1a
	//Set values for the index buffer
	WORD pIndices[] = { 0, 1, 2, 3, 2, 1,	//Top
					    4, 5, 6, 7, 6, 5,	//Face 1
					    8, 9,10,11,10, 9,	//Face 2
					   12,13,14,15,14,13,	//Face 3
					   16,17,18,19,18,17,	//Face 4
					   20,21,22,23,22,21};	//Bottom
	   
	//Get a pointer to the index buffer indices and lock the index buffer    
	m_pIndexBuffer->Lock(0, m_dwNumOfIndices * sizeof(WORD), (void**)&pBufferIndices, 0);

	//Copy our stored indices values into the index buffer
	memcpy(pBufferIndices, pIndices, m_dwNumOfIndices * sizeof(WORD));
	
	//Unlock the index buffer
	m_pIndexBuffer->Unlock();

	return true;
}

D3DXVECTOR3 CCuboid::GetTriangeNormal(D3DXVECTOR3* vVertex1, D3DXVECTOR3* vVertex2, D3DXVECTOR3* vVertex3)
{
	D3DXVECTOR3 vNormal;
	D3DXVECTOR3 v1;
	D3DXVECTOR3 v2;

	D3DXVec3Subtract(&v1, vVertex2, vVertex1);
	D3DXVec3Subtract(&v2, vVertex3, vVertex1);

	D3DXVec3Cross(&vNormal, &v1, &v2);

	D3DXVec3Normalize(&vNormal, &vNormal);

	return vNormal;
}

bool CCuboid::UpdateVertices()
{
	VOID* pVertices;
	D3DXVECTOR3 vNormal;

	CUBOID_CUSTOMVERTEX cvVertices[] =
	{	
		//Top Face
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.25f,},		//Vertex 0
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.25f,},		//Vertex 1
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.0f, 0.5f,},		//Vertex 2
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.5f,},		//Vertex 3
		
		//Face 1
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.25f,},		//Vertex 4
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.25f,},		//Vertex 5
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.5f,},		//Vertex 6
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.5f,},		//Vertex 7
		
		//Face 2
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.0f,},		//Vertex 8
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.0f,},		//Vertex 9
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.25f,},		//Vertex 10
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.25f,},		//Vertex 11
		
		//Face 3
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.75f, 0.25f,},		//Vertex 12
		{m_rX + (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 1.0f, 0.25f,},		//Vertex 13
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.75f, 0.5f,},		//Vertex 14
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 1.0f, 0.5f,},		//Vertex 15

		//Face 4
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.5f,},		//Vertex 16
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.5f,},		//Vertex 17
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.25f, 0.75f,},		//Vertex 18
		{m_rX - (m_rWidth / 2), m_rY + (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.75f,},		//Vertex 19

		//Bottom Face
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.25f,},		//Vertex 20
		{m_rX + (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.75f, 0.25f,},		//Vertex 21
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ - (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.5f, 0.5f,},		//Vertex 22
		{m_rX - (m_rWidth / 2), m_rY - (m_rHeight / 2), m_rZ + (m_rDepth / 2), 0.0f, 0.0f, 0.0f, 0.75f, 0.5f,},		//Vertex 23
	};
	
	//For each vertex, calculate and set the average normal
	for(unsigned i = 0; i < m_dwNumOfVertices; i+=4)
	{
		vNormal = GetTriangeNormal( &D3DXVECTOR3(cvVertices[i].x, cvVertices[i].y, cvVertices[i].z), &D3DXVECTOR3(cvVertices[i+1].x, cvVertices[i+1].y, cvVertices[i+1].z), &D3DXVECTOR3(cvVertices[i+2].x, cvVertices[i+2].y, cvVertices[i+2].z) );
		for ( unsigned j = i; j < i+4; ++j ) 
		{
			cvVertices[j].nx = vNormal.x;
			cvVertices[j].ny = vNormal.y;
			cvVertices[j].nz = vNormal.z;
		}
	}


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

bool CCuboid::SetSize(float rWidth, float rHeight, float rDepth)
{
	m_rWidth = rWidth;
	m_rHeight = rHeight;
	m_rDepth = rDepth;

	UpdateVertices();

	return true;
}

bool CCuboid::SetPosition(float x, float y, float z)
{
	m_rX = x;
	m_rY = y;
	m_rZ = z;

	UpdateVertices();

	return true;
}

bool CCuboid::SetTexture(LPCWSTR szTextureFilePath)
{
	if(FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, szTextureFilePath, &m_pTexture)))
	{
		return false;
	}

	return true;
}

bool CCuboid::SetMaterial(D3DCOLORVALUE rgbaDiffuse, D3DCOLORVALUE rgbaAmbient, D3DCOLORVALUE rgbaSpecular, D3DCOLORVALUE rgbaEmissive, float rPower)
{
	//Set the RGBA for diffuse light reflected from this material. 
	m_matMaterial.Diffuse = rgbaDiffuse; 

	//Set the RGBA for ambient light reflected from this material. 
	m_matMaterial.Ambient = rgbaAmbient; 

	//Set the color and sharpness of specular highlights for the material. 
	m_matMaterial.Specular = rgbaSpecular; 
	m_matMaterial.Power = rPower;

	//Set the RGBA for light emitted from this material. 
	m_matMaterial.Emissive = rgbaEmissive;

	return true;
}


