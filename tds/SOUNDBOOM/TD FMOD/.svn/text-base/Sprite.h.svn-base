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
		LPDIRECT3DDEVICE9 m_D3DDevice ;


	public:

		Sprite(LPDIRECT3DDEVICE9 _Device);
		~Sprite();
		void SetPosition( D3DXVECTOR2* _Position );
		void Move( float _fX, float _fY );
		void SetTexture( LPCWSTR _szTextureFilePath );
		void SetRectangle( short _iLeft, short _iTop, short _iBottom, short _iRight );
		void SetCenter( D3DXVECTOR2* _Center );
		void SetRotation( float _fRotation );
		void SetScaleCenter( D3DXVECTOR2* _ScaleCenter );
		void SetScale( D3DXVECTOR2* _Scale );
		void SetColor( short _iR, short _iG, short _iB );
		void Display();
};

#endif //SPRITE__H