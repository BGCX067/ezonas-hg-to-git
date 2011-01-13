/**
 * Code source Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */
#include "stdafx.h"
Sprite::Sprite (LPDIRECT3DDEVICE9  _Device)
{
	Device=_Device;
	m_pTexture= new LPDIRECT3DTEXTURE9();

	SetCenter(0.0, 0.0);
	SetRotation(0.0);
	SetScale(1.0, 1.0);
	SetPosition(20.0, 20.0);
	SetScaleCenter(60.0, 90.0);
	SetRectangle(0, 0, 300, 300);
	SetTexture("texture_test.bmp");
	D3DXCreateSprite(_Device, & m_pSprite);
}
Sprite::~Sprite()
{
	//SafeRelease (*m_pTexture);
	SafeRelease (m_pSprite);
}
void Sprite::Display()
{
	//start render loop with alpha enableb
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
/*
D3DXMATRIX* WINAPI D3DXMatrixTransformation2D
    ( D3DXMATRIX *pOut, CONST D3DXVECTOR2* pScalingCenter, 
      FLOAT ScalingRotation, CONST D3DXVECTOR2* pScaling, 
      CONST D3DXVECTOR2* pRotationCenter, FLOAT Rotation, 
      CONST D3DXVECTOR2* pTranslation);
*/

	D3DXMatrixTransformation2D
	(
		&mat,
		&m_pScaleCenter,
		0.5,
		&m_pScale,
		&m_pCenter,
		m_fRotation,
		&m_Translation
	);

	// Tell where the sprite will be rendered with a matrix
	m_pSprite->SetTransform(&mat);

	// Draw the sprite 
	m_pSprite->Draw (*m_pTexture, &m_pRect, NULL, NULL, m_Color);

	// Thats it
	m_pSprite->End();
}
void Sprite :: SetPosition(float x, float y)
{
	m_Translation.x = x;
	m_Translation.y = y;
}
/*
LPD3DXSPRITE m_pSprite;
LPDIRECT3DTEXTURE9 m_pTexture;
RECT *m_pRect;
D3DXVECTOR2 *m_pCenter;
float m_fRotation;
D3DXVECTOR2 *m_pScaleCenter;
D3DXVECTOR2 *m_pScale;
D3DXVECTOR2 m_Translation;
D3DCOLOR m_Color;
*/
void Sprite :: SetTexture(string filename)
{
	/*fstream f(filename);
	if (! f.is_open()) exit(0xdeadbeef);*/
	D3DXCreateTextureFromFile( Device, filename.c_str() , m_pTexture);
}
void Sprite :: SetRectangle(float x1, float y1, float x2, float y2)
{
	m_pRect.top = x1;
	m_pRect.left = y1;
	m_pRect.bottom = x2;
	m_pRect.right = y2;
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
//void Sprite :: SetColor(float r, float g, float b, float a)
void Sprite :: SetColor(int r, int g, int b, int a)
{
	m_Color = D3DCOLOR_ARGB(r, g, b, a);
}
