// Terrain.h: interface for the CTerrain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TERRAIN_H__605B63BD_B46A_44BF_A2F2_573132F97949__INCLUDED_)
#define AFX_TERRAIN_H__605B63BD_B46A_44BF_A2F2_573132F97949__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3dx9.h>
#include "Helper.h"

//Define a FVF for our terrain
#define TERRAIN_D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

class CTerrain  
{
private:
	//Define a custom vertex for our terrain
	struct TERRAIN_CUSTOMVERTEX
	{
		FLOAT x, y, z;		//Position of vertex in 3D space
		FLOAT nx, ny, nz;	//Lighting Normal
		FLOAT tu, tv;		//Texture coordinates
	};

public:
	bool SetMaterial(D3DCOLORVALUE _rgbaDiffuse, D3DCOLORVALUE _rgbaAmbient, D3DCOLORVALUE _rgbaSpecular, D3DCOLORVALUE _rgbaEmissive, float _fPower);
	bool SetTexture(LPCWSTR _szTextureFilePath);
	bool SetSize(WORD _wRows, WORD _wCols, float _fTileSize, WORD _wMaxHeight);
	DWORD Render();
	CTerrain(LPDIRECT3DDEVICE9 _pD3DDevice, WORD _wRows = 10, WORD _wCols = 10, float _fTileSize = 10.0, WORD _wMaxHeight = 15);
	virtual ~CTerrain();

private:

	D3DXVECTOR3 GetTriangeNormal(D3DXVECTOR3* vVertex1, D3DXVECTOR3* vVertex2, D3DXVECTOR3* vVertex3);
	bool CreateIndexBuffer();
	bool UpdateVertices();
	HRESULT CreateVertexBuffer();

	LPDIRECT3DDEVICE9 m_pD3DDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVertexBuffer;
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DMATERIAL9 m_matMaterial;
	LPDIRECT3DINDEXBUFFER9 m_pIndexBuffer;	

	WORD m_wRows;
	WORD m_wCols;
	WORD m_wMaxHeight;
	float m_fTileSize;

	DWORD m_dwNumOfVertices;	
	DWORD m_dwNumOfIndices;
	DWORD m_dwNumOfPolygons;

};

#endif // !defined(AFX_TERRAIN_H__605B63BD_B46A_44BF_A2F2_573132F97949__INCLUDED_)
