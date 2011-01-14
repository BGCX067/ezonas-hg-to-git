#include "stdafx.h"
Sprite::Sprite (LPDIRECT3DDEVICE9 _Device):
	Device(_Device)
{
	SetCenter(150.0, 150.0);
	SetRotation(0.0);
	SetScale(1.0, 1.0);
	SetPosition(0.0, 0.0);
	SetScaleCenter(0.0, 0.0);
	SetRectangle(0, 0, 300, 300);
	SetColor(255, 255, 255, 255);
	D3DXCreateSprite(Device, &m_pSprite);
	SetTexture("texture_test24.bmp");
}
Sprite::~Sprite()
{
	SafeRelease (m_pTexture);
	SafeRelease (m_pSprite);
}
void Sprite::Display()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat,&m_pScaleCenter,
									0.5,&m_pScale,&m_pCenter,
									m_fRotation,&m_Translation);

	m_pSprite->SetTransform(&mat);
	m_pSprite->Draw (m_pTexture, &m_pRect, NULL, NULL, m_Color);
	m_pSprite->End();
}
void Sprite :: SetPosition(float x, float y)
{
	m_Translation.x = x;
	m_Translation.y = y;
}
void Sprite :: SetTexture(string filename)
{
/*If the function succeeds, the return value is D3D_OK. If the function fails, the return value can be one of the 
following: D3DERR_NOTAVAILABLE, D3DERR_OUTOFVIDEOMEMORY, D3DERR_INVALIDCALL, 
D3DXERR_INVALIDDATA, E_OUTOFMEMORY.*/
	HRESULT ret = D3DXCreateTextureFromFile(Device, filename.c_str() , &m_pTexture);
	switch(ret)
	{
	case D3DERR_NOTAVAILABLE:
	case D3DERR_OUTOFVIDEOMEMORY:
	case D3DERR_INVALIDCALL:
	case D3DXERR_INVALIDDATA:
	case E_OUTOFMEMORY:
		exit(ret);
	case D3D_OK:
		break;
	}
}
void Sprite :: SetRectangle(float x1, float y1, float x2, float y2)
{
	m_pRect.left = x1;
	m_pRect.top = y1;
	m_pRect.right = x2;
	m_pRect.bottom = y2;
}
void Sprite :: SetCenter(float x, float y)
{
	m_pCenter.x = x;
	m_pCenter.y = y;
}
void Sprite :: SetRotation(float angle)
{
	m_fRotation = angle;
}
void Sprite :: SetScaleCenter(float x, float y)
{
	m_pScaleCenter.x = x;
	m_pScaleCenter.y = y;
}
void Sprite :: SetScale(float x, float y)
{
	m_pScale.x = x;
	m_pScale.y = y;
}
void Sprite :: SetColor(int r, int g, int b, int a)
{
	m_Color = D3DCOLOR_ARGB(r, g, b, a);
}
