/**
 * Code source Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#include "Sprite.h"

Sprite::Sprite( LPDIRECT3DDEVICE9 _Device )
{
}

Sprite::~Sprite()
{
	SafeDelete( m_pRect );
	SafeDelete( m_pCenter );
	SafeDelete( m_pScaleCenter );
	SafeDelete( m_pScale );
	SafeRelease( m_pTexture );
	SafeRelease( m_pSprite );
}

void Sprite::Display()
{
	//start render loop with alpha enableb
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat,m_pScaleCenter,0.5,m_pScale,m_pCenter,m_fRotation,&m_Translation);

	// Tell where the sprite will be rendered with a matrix
	m_pSprite->SetTransform(&mat);

	// Draw the sprite 
	m_pSprite->Draw( m_pTexture, m_pRect, NULL, NULL, m_Color );

	// Thats it
	m_pSprite->End();
}