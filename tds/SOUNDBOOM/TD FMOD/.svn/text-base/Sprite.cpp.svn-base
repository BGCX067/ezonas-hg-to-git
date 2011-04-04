/**
 * Code source Sprite
 * 
 * @author  Fabsther
 * @since   03/05/2010
 * @version 1.0
 */

#include "Sprite.h"

Sprite::Sprite(LPDIRECT3DDEVICE9 _D3DDevice)
{
	//init translation
	m_Translation.x =0.0f;	
	m_Translation.y =0.0f;

	//init rectangle
	m_pRect = NULL;

	//init center
	m_pCenter = NULL;
	
	//init de la rotation
	m_fRotation = 0.0f;

	//init du centre de scale
	m_pScaleCenter = NULL;

	//init du scale
	m_pScale = NULL;

	//init color
	m_Color = D3DCOLOR_XRGB(255, 255, 255);

	//init pointeur texture
	m_pTexture = NULL;

	m_D3DDevice = _D3DDevice ;

	//creation du sprite
	if ( FAILED(D3DXCreateSprite( _D3DDevice, &m_pSprite ) ) )
	{
		OutputDebugString(L"Failed to create Sprite.\n");
	}

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

void Sprite::SetPosition( D3DXVECTOR2* _Position )
{
	m_Translation = *_Position;
}

void Sprite::SetTexture( LPCWSTR _szTextureFilePath )
{
	if( FAILED( D3DXCreateTextureFromFile(m_D3DDevice, _szTextureFilePath, &m_pTexture ) ) )
	{
		OutputDebugString(L"Failed to load texture Sprite.\n");
	}
}

void Sprite::SetRectangle( short _iLeft, short _iTop, short _iBottom, short _iRight )
{
	m_pRect = new RECT();
	m_pRect->left = _iLeft; 
    m_pRect->top = _iTop; 
    m_pRect->bottom = _iBottom; 
    m_pRect->right = _iRight;   
}

void Sprite::SetCenter( D3DXVECTOR2* _Center )
{
	m_pCenter = new D3DXVECTOR2( _Center->x,  _Center->y );
}

void Sprite::SetColor( short _iR, short _iG, short _iB )
{
	m_Color = D3DCOLOR_XRGB(_iR, _iG, _iB);
}

void Sprite::SetRotation( float _fRotation )
{
	m_fRotation = _fRotation;
}

void Sprite::SetScaleCenter( D3DXVECTOR2* _ScaleCenter )
{
	m_pScaleCenter = new D3DXVECTOR2( _ScaleCenter->x,  _ScaleCenter->y );
}

void Sprite::SetScale( D3DXVECTOR2* _Scale )
{
	m_pScale = new D3DXVECTOR2( _Scale->x,  _Scale->y );
}

void Sprite::Move( float _fX, float _fY )
{
	m_Translation.x += _fX;
	m_Translation.y += _fY;
}

void Sprite::Display()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat,m_pScaleCenter,0.5,m_pScale,m_pCenter,m_fRotation,&m_Translation);

	// Tell the sprite about the matrix
	m_pSprite->SetTransform(&mat);

	// Draw the sprite 
	m_pSprite->Draw( m_pTexture, m_pRect, NULL, NULL, m_Color );

	// Thats it
	m_pSprite->End();
}