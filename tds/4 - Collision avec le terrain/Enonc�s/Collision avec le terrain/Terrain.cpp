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
	unsigned k = 0;
    for ( unsigned i = 0; i < m_wCols ; ++i )
	{
		for ( unsigned j = 0; j < m_wRows; ++j ) 
		{
			pIndices[k] = ( i ) + ( j * (m_wRows+1) );
			pIndices[k+1] = ( i ) + ( j * (m_wRows+1) ) + 1;
			pIndices[k+2] = ( i ) + ( j * (m_wRows+1) ) + (m_wRows+1);
			pIndices[k+3] = ( i ) + ( j * (m_wRows+1) ) + (m_wRows+2);
			pIndices[k+4] = ( i ) + ( j * (m_wRows+1) ) + (m_wRows+1);
			pIndices[k+5] = ( i ) + ( j * (m_wRows+1) ) + 1;
			k += 6;
		}
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

	TERRAIN_CUSTOMVERTEX* pcvVertices = new TERRAIN_CUSTOMVERTEX[m_dwNumOfVertices];	//Array holds the veritces																				

	//Initialise the random number generator
	srand(timeGetTime());  

	//Clear memory and setup vertices for terrain
	//Setup vertices for terrain
	unsigned k = 0;
	for ( unsigned i = 0; i < ( (unsigned) m_wCols + 1 ); i++)
	{
		for ( unsigned j = 0; j < ( (unsigned) m_wRows + 1 ); j++)
		{
			pcvVertices[k].x = i * m_fTileSize - ( m_fTileSize * m_wCols / 2 );
			pcvVertices[k].z = j * m_fTileSize - ( m_fTileSize * m_wRows / 2 );
			pcvVertices[k].y = (m_wMaxHeight) * ( ( (float) ( rand() % 100 ) ) / 100.0f )  ;
			++k;
		}
	}

	//Get a pointer to the index buffer indices and lock the index buffer    
	m_pIndexBuffer->Lock(0, m_dwNumOfIndices * sizeof(WORD), (void**)&pBufferIndices, D3DLOCK_READONLY);

	//For each triangle, count the number of times each vertex is used and
	//add together the normals of faces that share a vertex
	for ( unsigned i = 0 ; i < ( (unsigned) m_dwNumOfVertices + 1 ); i++)
	{
		vNormal.x = 0;
		vNormal.y = 0;
		vNormal.z = 0;

		//si  le vertex n'est pas en haut ou a droite
		if ( ( ( i + 1 ) %  ( m_wRows + 1 )  != 1 ) && ( i  <  ( m_dwNumOfVertices - ( m_wRows ) ) ) )
		{
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i + ( m_wRows + 1 ) - 1 ].x, pcvVertices[ i + ( m_wRows + 1 ) - 1 ].y, pcvVertices[ i + ( m_wRows + 1 ) - 1 ].z ),&D3DXVECTOR3( pcvVertices[ i - 1 ].x, pcvVertices[ i - 1 ].y, pcvVertices[ i - 1 ].z ) );
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i + ( m_wRows + 1 ) ].x, pcvVertices[ i + ( m_wRows + 1 ) ].y, pcvVertices[ i + ( m_wRows + 1 ) ].z ),&D3DXVECTOR3( pcvVertices[ i + ( m_wRows + 1 ) - 1 ].x, pcvVertices[ i + ( m_wRows + 1 ) - 1 ].y, pcvVertices[ i + ( m_wRows + 1 ) - 1 ].z ) );
		}

		//si  le vertex n'est pas en bas ou a gauche
		if ( ( i %  ( m_wRows + 1 )  != 0 ) && ( i  > ( ( unsigned ) m_wRows ) ) )
		{
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i - ( m_wRows + 1 ) ].x, pcvVertices[ i - ( m_wRows + 1 ) ].y, pcvVertices[ i - ( m_wRows + 1 ) ].z ),&D3DXVECTOR3( pcvVertices[ i - ( m_wRows + 1 ) + 1 ].x, pcvVertices[ i - ( m_wRows + 1 ) + 1 ].y, pcvVertices[ i - ( m_wRows + 1 ) + 1 ].z ) );
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i - ( m_wRows + 1 ) + 1 ].x, pcvVertices[ i - ( m_wRows + 1 ) + 1 ].y, pcvVertices[ i - ( m_wRows + 1 ) + 1 ].z ),&D3DXVECTOR3( pcvVertices[ i + 1 ].x, pcvVertices[ i + 1 ].y, pcvVertices[ i + 1 ].z ) );
		}


		//si  le vertex n'est pas en haut ou a gauche
		if ( ( ( i + 1 ) %  ( m_wRows + 1 )  != 1 ) && ( i  > ( unsigned ) ( m_wRows ) ) )
		{
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i - 1 ].x, pcvVertices[ i - 1 ].y, pcvVertices[ i - 1 ].z ),&D3DXVECTOR3( pcvVertices[ i - ( m_wRows + 1 ) ].x, pcvVertices[ i - ( m_wRows + 1 ) ].y, pcvVertices[ i - ( m_wRows + 1 ) ].z ) );
		}

		//si  le vertex n'est pas en bas ou a droite
		if ( ( i %  ( m_wRows + 1 )  != 0 ) && ( i  <  ( m_dwNumOfVertices - ( m_wRows ) ) ) )
		{
			vNormal += GetTriangeNormal( &D3DXVECTOR3( pcvVertices[ i ].x, pcvVertices[ i ].y, pcvVertices[ i ].z ) , &D3DXVECTOR3( pcvVertices[ i + 1 ].x, pcvVertices[ i + 1 ].y, pcvVertices[ i + 1 ].z ),&D3DXVECTOR3( pcvVertices[ i + ( m_wRows + 1 ) ].x, pcvVertices[ i + ( m_wRows + 1 ) ].y, pcvVertices[ i + ( m_wRows + 1 ) ].z ) );
		}

		D3DXVec3Normalize(&vNormal, &vNormal);
		pcvVertices[i].nx = vNormal.x;
		pcvVertices[i].ny = vNormal.y;
		pcvVertices[i].nz = vNormal.z;
		
	}


	//Unlock the index buffer
	m_pIndexBuffer->Unlock();

	//For each vertex, calculate the textures coordonates
	int iX, iY;
	k = 0;
	for ( unsigned i = 0; i < ( (unsigned) m_wCols + 1 ); i++)
	{
		iX = ( i % 2 );
		iY = 0;
		for ( unsigned j = 0; j < ( (unsigned) m_wRows + 1 ); j++)
		{
			pcvVertices[k].tu = ( float )iX;
			pcvVertices[k].tv = ( float )iY;
			iY = ( iY + 1 ) % 2 ; 
			++k;
		}
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
	SafeDelete( pcvVertices );
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