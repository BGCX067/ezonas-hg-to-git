// Terrain.cpp: implementation of the CTerrain class.
//
//////////////////////////////////////////////////////////////////////

#include "Terrain.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTerrain::CTerrain(LPDIRECT3DDEVICE9 _pD3DDevice, WORD _wRows, WORD _wCols, float _fTileSize, WORD _wMaxHeight)
{
	m_pD3DDevice = _pD3DDevice;
	m_pVertexBuffer = NULL;
	m_pIndexBuffer = NULL;
	m_pTexture = NULL;

	//Set a default size and position
	m_wRows = _wRows;
	m_wCols = _wCols;
	
	//Set the tile size for the terrain
	m_fTileSize = _fTileSize;

	//Set the max height for any vertex
	m_wMaxHeight = _wMaxHeight;

	//Setup counts for this object
	m_dwNumOfVertices = (m_wCols + 1) * (m_wRows + 1);
	m_dwNumOfPolygons = m_wRows * m_wCols * 2;
	m_dwNumOfIndices  = m_dwNumOfPolygons * 3;

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

CTerrain::~CTerrain()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pIndexBuffer);
	SafeRelease(m_pVertexBuffer);
}

DWORD CTerrain::Render()
{
	m_pD3DDevice->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(TERRAIN_CUSTOMVERTEX));
    m_pD3DDevice->SetFVF( TERRAIN_D3DFVF_CUSTOMVERTEX );
	
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

HRESULT CTerrain::CreateVertexBuffer()
{
    //Create the vertex buffer from our device.
    if(FAILED(m_pD3DDevice->CreateVertexBuffer(m_dwNumOfVertices * sizeof(TERRAIN_CUSTOMVERTEX),
                                               0, TERRAIN_D3DFVF_CUSTOMVERTEX,
                                               D3DPOOL_DEFAULT, &m_pVertexBuffer, NULL)))
    {
        return E_FAIL;
    }

    return S_OK;
}

bool CTerrain::CreateIndexBuffer()
{
	VOID* pBufferIndices;

	//Create the index buffer from our device
	if(FAILED(m_pD3DDevice->CreateIndexBuffer(m_dwNumOfIndices * sizeof(WORD), 
											  0, D3DFMT_INDEX16, D3DPOOL_MANAGED,
											  &m_pIndexBuffer, NULL)))
	{
	    return false;
	}
	
	
	//Set values for the index buffer
	WORD* pIndices = new WORD[m_dwNumOfIndices];	//Array holds the indices
	
    // Indices values initialisation
	WORD a = m_wCols + 1;
	WORD b = 0;
	WORD c = a + 1;

	WORD x, z, i = 0;
	for(z = 0; z < m_wRows; z++)
	{
		for(x = 0; x < m_wCols; x++)
		{
			pIndices[i]	= a;
			pIndices[i + 1]	= b;
			pIndices[i + 2]	= c;
			pIndices[i + 3]	= b + 1;
			pIndices[i + 4]	= c;
			pIndices[i + 5]	= b;

			a++;
			b++;
			c++;
			i += 6;
		}

		a = c;
		b++;
		c++;
	}

	//Get a pointer to the index buffer indices and lock the index buffer    
	m_pIndexBuffer->Lock(0, m_dwNumOfIndices * sizeof(WORD), (void**)&pBufferIndices, 0);

	//Copy our stored indices values into the index buffer
	memcpy(pBufferIndices, pIndices, m_dwNumOfIndices * sizeof(WORD));
	
	//Unlock the index buffer
	m_pIndexBuffer->Unlock();

	//Clean up
	delete pIndices;
	pIndices = NULL;

	return true;
}

D3DXVECTOR3 CTerrain::GetTriangeNormal(D3DXVECTOR3* vVertex1, D3DXVECTOR3* vVertex2, D3DXVECTOR3* vVertex3)
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

bool CTerrain::UpdateVertices()
{
	DWORD i = 0;
	VOID* pVertices;
	WORD* pBufferIndices;
	D3DXVECTOR3 vNormal;
	DWORD dwVertex1;
	DWORD dwVertex2;
	DWORD dwVertex3;
	float fNoise = 0.0f;

	WORD* pNumOfSharedPolygons = new WORD[m_dwNumOfVertices];							//Array holds how many times this vertex is shared
	D3DVECTOR* pSumVertexNormal = new D3DVECTOR[m_dwNumOfVertices];						//Array holds sum of all face normals for shared vertex
	TERRAIN_CUSTOMVERTEX* pcvVertices = new TERRAIN_CUSTOMVERTEX[m_dwNumOfVertices];	//Array holds the veritces																				

	float x, z;

	//Centre terrain around the origin
	float zStart	= (float)(0.0 - (m_wRows/2.0));
	float zEnd		= (float)(m_wRows/2.0);
	float xStart	= (float)(0.0 - (m_wCols/2.0));
	float xEnd		= (float)(m_wCols/2.0);

	//Initialise the random number generator
	srand(timeGetTime());  

	//Clear memory and setup vertices for terrain
	for(z = zStart; z <= zEnd; z++)
	{
		for(x = xStart; x <= xEnd; x++)
		{
			pNumOfSharedPolygons[i] = 0;
			pSumVertexNormal[i] = D3DXVECTOR3(0,0,0);

			//Make sure that the edges are all the same level
			if( (m_wMaxHeight==0)
				|| (z == zStart) || (z == zEnd) || (x == xStart) || (x == xEnd))
			{
				pcvVertices[i].y = 0.0;
			}
			else
			{
				fNoise = (float)(rand() % m_wMaxHeight);

				//Set a random height for y
				pcvVertices[i].y = fNoise;
			}
			
            pcvVertices[i].x = x * m_fTileSize;

			pcvVertices[i].z = -z * m_fTileSize;	

			pcvVertices[i].nx = 0.0;
			pcvVertices[i].ny = 0.0;
			pcvVertices[i].nz = 0.0;
			
			if(((int)z % 2) == 0)
			{
				if(((int)x % 2) == 0)
				{
					pcvVertices[i].tu = 0.0;
					pcvVertices[i].tv = 0.0;
				}
				else
				{
					pcvVertices[i].tu = 1.0;
					pcvVertices[i].tv = 0.0;
				}
			}
			else
			{
				if(((int)x % 2) == 0)
				{
					pcvVertices[i].tu = 0.0;
					pcvVertices[i].tv = 1.0;
				}
				else
				{
					pcvVertices[i].tu = 1.0;
					pcvVertices[i].tv = 1.0;
				}
			}

			i++;
		}
	}


	//Get a pointer to the index buffer indices and lock the index buffer    
	m_pIndexBuffer->Lock(0, m_dwNumOfIndices * sizeof(WORD), (void**)&pBufferIndices, D3DLOCK_READONLY);

	//For each triangle, count the number of times each vertex is used and
	//add together the normals of faces that share a vertex
	for(i = 0; i < m_dwNumOfIndices; i += 3)
	{
		dwVertex1 = pBufferIndices[i];
		dwVertex2 = pBufferIndices[i + 1];
		dwVertex3 = pBufferIndices[i + 2];

		vNormal = GetTriangeNormal(&D3DXVECTOR3(pcvVertices[dwVertex1].x, pcvVertices[dwVertex1].y, pcvVertices[dwVertex1].z), 
								   &D3DXVECTOR3(pcvVertices[dwVertex2].x, pcvVertices[dwVertex2].y, pcvVertices[dwVertex2].z), 
								   &D3DXVECTOR3(pcvVertices[dwVertex3].x, pcvVertices[dwVertex3].y, pcvVertices[dwVertex3].z));

		
		pNumOfSharedPolygons[dwVertex1]++;
		pNumOfSharedPolygons[dwVertex2]++;
		pNumOfSharedPolygons[dwVertex3]++;

		pSumVertexNormal[dwVertex1].x += vNormal.x;
		pSumVertexNormal[dwVertex1].y += vNormal.y;
		pSumVertexNormal[dwVertex1].z += vNormal.z;
		
		pSumVertexNormal[dwVertex2].x += vNormal.x;
		pSumVertexNormal[dwVertex2].y += vNormal.y;
		pSumVertexNormal[dwVertex2].z += vNormal.z;

		pSumVertexNormal[dwVertex3].x += vNormal.x;
		pSumVertexNormal[dwVertex3].y += vNormal.y;
		pSumVertexNormal[dwVertex3].z += vNormal.z;
	}


	//Unlock the index buffer
	m_pIndexBuffer->Unlock();

	//For each vertex, calculate the average normal
	for(i = 0; i < m_dwNumOfVertices; i++)
	{
		vNormal.x = pSumVertexNormal[i].x / pNumOfSharedPolygons[i];
		vNormal.y = pSumVertexNormal[i].y / pNumOfSharedPolygons[i];
		vNormal.z = pSumVertexNormal[i].z / pNumOfSharedPolygons[i];

		D3DXVec3Normalize(&vNormal, &vNormal);

		pcvVertices[i].nx = vNormal.x;
		pcvVertices[i].ny = vNormal.y;
		pcvVertices[i].nz = vNormal.z;
	}


	//Get a pointer to the vertex buffer vertices and lock the vertex buffer
    if(FAILED(m_pVertexBuffer->Lock(0, m_dwNumOfVertices * sizeof(TERRAIN_CUSTOMVERTEX), (void**)&pVertices, 0)))
    {
        OutputDebugString(L"Lock Vertex Buffer Failed!\n");
		return false;
    }

    //Copy our stored vertices values into the vertex buffer
    memcpy(pVertices, pcvVertices, m_dwNumOfVertices * sizeof(TERRAIN_CUSTOMVERTEX));

    //Unlock the vertex buffer
    m_pVertexBuffer->Unlock();
	

	//Clean up
	delete pNumOfSharedPolygons;
	delete pSumVertexNormal;
	delete pcvVertices;

	pNumOfSharedPolygons = NULL;
	pSumVertexNormal = NULL;
	pcvVertices = NULL;

	return true;
}

bool CTerrain::SetSize(WORD _wRows, WORD _wCols, float _fTileSize, WORD _wMaxHeight)
{
	//Set size
	m_wRows = _wRows;
	m_wCols = _wCols;
	
	//Set the tile size for the terrain
	m_fTileSize = _fTileSize;

	//Set the max height for any vertex
	m_wMaxHeight = _wMaxHeight;

	//Setup counts for this object
	m_dwNumOfVertices = (m_wCols + 1)  * (m_wRows + 1);	
	m_dwNumOfPolygons = m_wRows * m_wCols * 2;
	m_dwNumOfIndices  = m_dwNumOfPolygons * 3;

	UpdateVertices();

	return true;
}

bool CTerrain::SetTexture(LPCWSTR _szTextureFilePath)
{
	if(FAILED(D3DXCreateTextureFromFile(m_pD3DDevice, _szTextureFilePath, &m_pTexture)))
	{
		OutputDebugString(L"Failed to load texture.");
		return false;
	}

	return true;
}

bool CTerrain::SetMaterial(D3DCOLORVALUE _rgbaDiffuse, D3DCOLORVALUE _rgbaAmbient, D3DCOLORVALUE _rgbaSpecular, D3DCOLORVALUE _rgbaEmissive, float _fPower)
{
	//Set the RGBA for diffuse light reflected from this material. 
	m_matMaterial.Diffuse = _rgbaDiffuse; 

	//Set the RGBA for ambient light reflected from this material. 
	m_matMaterial.Ambient = _rgbaAmbient; 

	//Set the color and sharpness of specular highlights for the material. 
	m_matMaterial.Specular = _rgbaSpecular; 
	m_matMaterial.Power = _fPower;

	//Set the RGBA for light emitted from this material. 
	m_matMaterial.Emissive = _rgbaEmissive;

	return true;
}

bool CTerrain::CollisionFlatPlane(D3DXVECTOR3* _Q)
{
    if (_Q->y < 0.0f)
    {
        _Q->y = 0.0f;
        return true;
    }

    return false;
}

bool CTerrain::CollisionHeightMap(D3DXVECTOR3* _Q)
{
	WORD* pBufferIndices;
	TERRAIN_CUSTOMVERTEX* pVertices;
	DWORD dwVertex1;
	DWORD dwVertex2;
	DWORD dwVertex3;
    D3DXVECTOR3 vP0;
    D3DXVECTOR3 vP1;
    D3DXVECTOR3 vP2;

	//Get a pointer to the index buffer indices and lock the index buffer    
	m_pIndexBuffer->Lock(0, m_dwNumOfIndices * sizeof(WORD), (void**)&pBufferIndices, D3DLOCK_READONLY);

    m_pVertexBuffer->Lock(0, m_dwNumOfVertices * sizeof(TERRAIN_CUSTOMVERTEX), (void**)&pVertices, D3DLOCK_READONLY);


    // Determine quad containing Q
	WORD x, z, i = 0;
    WORD xQ = -1, zQ = -1;

    // if out of bound in z, no collision
    if (_Q->z > pVertices[0].z || _Q->z <= pVertices[m_wRows*(m_wCols+1)].z)
    {
        return false;
    }
    // if out of bound in x, no collision
    if (_Q->x < pVertices[0].x || _Q->x <= pVertices[m_wRows*(m_wCols+1)].x)
    {
        return false;
    }

    for(z = 0; z < m_wRows; z++)
    {
        if (_Q->z > pVertices[(z+1)*(m_wCols+1)].z)
        {
            zQ = z;
            break;
        }
    }
    for(x = 0; x < m_wCols; x++)
    {
        if (_Q->x < pVertices[x+1].x)
        {
            xQ = x;
            break;
        }
    }

    // find Quad's initial index
    i = (zQ*(m_wCols) + xQ)*6;

    // quad found, find the triangle

    // get first triangle (inferior)
    dwVertex1 = pBufferIndices[i];
    dwVertex2 = pBufferIndices[i + 1];
    dwVertex3 = pBufferIndices[i + 2];
    vP0 = D3DXVECTOR3(pVertices[dwVertex1].x, pVertices[dwVertex1].y, pVertices[dwVertex1].z);
    vP1 = D3DXVECTOR3(pVertices[dwVertex2].x, pVertices[dwVertex2].y, pVertices[dwVertex2].z);
    vP2 = D3DXVECTOR3(pVertices[dwVertex3].x, pVertices[dwVertex3].y, pVertices[dwVertex3].z);

    // compute min and max in x and z
    float ZMax = max(max (vP0.z, vP1.z), vP2.z);
    float XMax = max(max (vP0.x, vP1.x), vP2.x);
    float ZMin = min(min (vP0.z, vP1.z), vP2.z);
    float XMin = min(min (vP0.x, vP1.x), vP2.x);

    float dz = (_Q->z - ZMin)/(ZMax - ZMin);
    float dx = (_Q->x - XMin)/(XMax - XMin);

    // change if superior triangle
    if (dz > 1-dx)
    {
	    dwVertex1 = pBufferIndices[i + 3];
	    dwVertex2 = pBufferIndices[i + 4];
	    dwVertex3 = pBufferIndices[i + 5];

	    vP0 = D3DXVECTOR3(pVertices[dwVertex1].x, pVertices[dwVertex1].y, pVertices[dwVertex1].z);
	    vP1 = D3DXVECTOR3(pVertices[dwVertex2].x, pVertices[dwVertex2].y, pVertices[dwVertex2].z);
        vP2 = D3DXVECTOR3(pVertices[dwVertex3].x, pVertices[dwVertex3].y, pVertices[dwVertex3].z);
    }

    // Compute normal
	D3DXVECTOR3 N = GetTriangeNormal( &vP0, &vP1, &vP2 );

    // Resolve height on map
    float dot = D3DXVec3Dot(&N, &vP0);
    float fQOnPlane = (-(N.x*_Q->x)-(N.z*_Q->z)+dot)/N.y;

    // Recalage
    if (_Q->y < fQOnPlane)
    {
        _Q->y = fQOnPlane;
    }

    //Unlock the vertex buffer
    m_pVertexBuffer->Unlock();

	//Unlock the index buffer
	m_pIndexBuffer->Unlock();

    return false;
}