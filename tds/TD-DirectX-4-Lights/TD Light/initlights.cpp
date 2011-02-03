#include "Game.h"
void Game::InitialiseLights()
{	
	//Turn on lighting
    m_D3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//setting des paramètres
	D3DXVECTOR3 Direction = D3DXVECTOR3(1.0, -1.0, 0.0); // directionnal
	D3DXVECTOR3 Position1 = D3DXVECTOR3(0, 10.0, 0.0); // point
	D3DXVECTOR3 Position2 = D3DXVECTOR3(-10.0, 0.0, 0.0); // spot 1
	D3DXVECTOR3 Direction2 = D3DXVECTOR3(1.0, 0.0, 0.0);
	D3DXVECTOR3 Position3 = D3DXVECTOR3(10.0, 0.0, 0.0); // spot 2
	D3DXVECTOR3 Direction3 = D3DXVECTOR3(-1.0, 0.0, 0.0);

// Light class is plain useless, I'll create the light and set their
// parameters here.

// ------------- directionnal, red -------------
	D3DLIGHT9 l_dir;
	ZeroMemory(&l_dir, sizeof(D3DLIGHT9));
	l_dir.Type = D3DLIGHT_DIRECTIONAL;
	l_dir.Diffuse.r = 1.0f; l_dir.Diffuse.g = 0.0f; l_dir.Diffuse.b = 0.0f;
	l_dir.Ambient.r = 0.2f; l_dir.Ambient.g = 0.0f; l_dir.Ambient.b = 0.0f;
	l_dir.Specular.r = 0.0f; l_dir.Specular.g	= 0.0f; l_dir.Specular.b	= 0.0f;
	l_dir.Direction = Direction;

// ------------- point, purple -------------
	D3DLIGHT9 l_pt;
	ZeroMemory(&l_pt, sizeof(D3DLIGHT9));
	l_pt.Type = D3DLIGHT_POINT;
	l_pt.Diffuse.r = 1.0f; l_pt.Diffuse.g = 0.0f; l_pt.Diffuse.b = 1.0f;
	l_pt.Ambient.r = 0.2f; l_pt.Ambient.g = 0.0f; l_pt.Ambient.b = 0.2f;
	l_pt.Specular.r = 0.0f; l_pt.Specular.g	= 0.0f; l_pt.Specular.b = 0.0f;
	l_pt.Position = Position1;
	l_pt.Range = 10.0;
	
// ------------- spot, green -------------
	D3DLIGHT9 l_spot1;
	ZeroMemory(&l_spot1, sizeof(D3DLIGHT9));
	l_spot1.Type = D3DLIGHT_SPOT;
	l_spot1.Diffuse.r = 0.0f; l_spot1.Diffuse.g = 1.0f; l_spot1.Diffuse.b = 0.0f;
	l_spot1.Ambient.r = 0.0f; l_spot1.Ambient.g = 0.2f; l_spot1.Ambient.b = 0.0f;
	l_spot1.Specular.r = 0.0f; l_spot1.Specular.g = 0.0f; l_spot1.Specular.b = 0.0f;
	l_spot1.Position = Position2;
	l_spot1.Direction = Direction2;
	l_spot1.Range = 150.0f;
	// l_spot1.Phi = 150.0f;
	l_spot1.Theta = 150.0f;
	
	
// ------------- spot, blue -------------
	D3DLIGHT9 l_spot2;
	ZeroMemory(&l_spot2, sizeof(D3DLIGHT9));
	l_spot2.Type = D3DLIGHT_SPOT;
	l_spot2.Diffuse.r = 0.0f; l_spot2.Diffuse.g = 0.0f; l_spot2.Diffuse.b = 1.0f;
	l_spot2.Ambient.r = 0.0f; l_spot2.Ambient.g = 0.0f; l_spot2.Ambient.b = 0.2f;
	l_spot2.Specular.r = 0.0f; l_spot2.Specular.g	= 0.0f; l_spot2.Specular.b = 0.0f;
	l_spot2.Position = Position3;
	l_spot2.Direction = Direction3;
	l_spot2.Range = 150.0f;
	// l_spot2.Phi = 150.0f;
	l_spot2.Theta = 150.0f;
//
	m_D3DDevice->SetLight(0, &l_dir); // red dir
	m_D3DDevice->SetLight(1, &l_pt); // purple point
	m_D3DDevice->SetLight(2, &l_spot1); // green spot
	m_D3DDevice->SetLight(3, &l_spot2); // blue spot

	m_D3DDevice->LightEnable(0, TRUE);
	m_D3DDevice->LightEnable(1, TRUE);
	m_D3DDevice->LightEnable(2, TRUE);
	m_D3DDevice->LightEnable(3, TRUE);

/*	
	D3DXVECTOR3 Direction = D3DXVECTOR3(1.0, -1.0, 0.0); // directionnal
	D3DXVECTOR3 Position1 = D3DXVECTOR3(0, 10.0, 0.0); // point
	D3DXVECTOR3 Position2 = D3DXVECTOR3(-10.0, 0.0, 0.0); // spot 1
	D3DXVECTOR3 Direction2 = D3DXVECTOR3(1.0, 0.0, 0.0);
	D3DXVECTOR3 Position3 = D3DXVECTOR3(10.0, 0.0, 0.0); // spot 2
	D3DXVECTOR3 Direction3 = D3DXVECTOR3(-1.0, 0.0, 0.0);
*/
	float fRange = 150.0f; // ??

	//utilisation des nouvelles lights

	//Set ambient light level   
	//------> à desactiver une fois les lights implémentées
//	m_D3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(200, 200, 200));
}
