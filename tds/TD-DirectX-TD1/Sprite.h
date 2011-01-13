/**
 * Header Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#ifndef SPRITE__H
#define SPRITE__H

#include "stdafx.h"
class Sprite
{
protected:
	LPD3DXSPRITE m_pSprite;
	LPDIRECT3DTEXTURE9 * m_pTexture;
	RECT m_pRect;
	D3DXVECTOR2 m_pCenter;
	float m_fRotation;
	D3DXVECTOR2 m_pScaleCenter;
	D3DXVECTOR2 m_pScale;
	D3DXVECTOR2 m_Translation;
	D3DCOLOR m_Color;
	LPDIRECT3DDEVICE9 Device;

public:
	Sprite (LPDIRECT3DDEVICE9 _Device);
	~Sprite();
	void Display();

	void SetPosition(float x, float y);
	void SetTexture(string filename = "texture_test.bmp");
	void SetRectangle(float x1, float y1, float x2, float y2);
	void SetCenter(float x, float y);
	void SetRotation(float angle);
	void SetScaleCenter(float x, float y);
	void SetScale(float x, float y);
	void SetColor(int r, int g, int b, int a);
};

#endif //SPRITE__H