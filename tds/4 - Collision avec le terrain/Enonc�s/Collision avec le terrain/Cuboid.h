// Cuboid.h: interface for the CCuboid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUBOID_H__AE25AF5F_AE56_48F5_99DC_47CAAA14F245__INCLUDED_)
#define AFX_CUBOID_H__AE25AF5F_AE56_48F5_99DC_47CAAA14F245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <d3dx9.h>
#include "helper.h"

//Define a FVF for our cubiods
#define CUBOID_D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_NORMAL)

class CCuboid
{
private:
	//Define a custom vertex for our cubiods
	struct CUBOID_CUSTOMVERTEX
	{
		FLOAT x, y, z;		//Position of vertex in 3D space
		FLOAT nx, ny, nz;	//Lighting Normal
	};

public:
	bool SetMaterial(D3DCOLORVALUE _rgbaDiffuse, D3DCOLORVALUE _rgbaAmbient, D3DCOLORVALUE _rgbaSpecular, D3DCOLORVALUE _rgbaEmissive, float _fPower);
	bool SetTexture(LPCWSTR _szTextureFilePath);
	bool SetPosition(float _fx, float _fy, float _fz);
	bool SetSize(float _fWidth, float _fHeight, float _fDepth);
	DWORD Render();
	CCuboid(LPDIRECT3DDEVICE9 _pD3DDevice, float _fx = 0.0, float _fy = 0.0, float _fz = 0.0);
	virtual ~CCuboid();

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

	float m_fWidth;
	float m_fHeight;
	float m_fDepth;
	float m_fX;
	float m_fY;
	float m_fZ;

	DWORD m_dwNumOfVertices;	
	DWORD m_dwNumOfIndices;
	DWORD m_dwNumOfPolygons;
};

#endif // !defined(AFX_CUBOID_H__AE25AF5F_AE56_48F5_99DC_47CAAA14F245__INCLUDED_)
