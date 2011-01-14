/**
 * Header Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#ifndef SPRITE__H
#define SPRITE__H

#include <d3dx9.h>
#include "helper.h"

class Sprite
{
	protected:

		LPD3DXSPRITE m_pSprite;
		LPDIRECT3DTEXTURE9 m_pTexture;
		RECT *m_pRect;
		D3DXVECTOR2 *m_pCenter;
		float m_fRotation;
		D3DXVECTOR2 *m_pScaleCenter;
		D3DXVECTOR2 *m_pScale;
		D3DXVECTOR2 m_Translation;
		D3DCOLOR m_Color;


	public:

		Sprite( LPDIRECT3DDEVICE9 _Device );
		~Sprite();
		void Display();
};

#endif //SPRITE__H