/**
 * Light.cpp
 * 
 * @author  Fabsther
 * @since   14/06/2010
 * @version 1.0
 */

#include "Light.h"
Light :: Light(LPDIRECT3DDEVICE9 _D3DDevice, short _iIndice)
{
	//init de la light
	ZeroMemory( &m_pLight, sizeof(D3DLIGHT9));

	m_pLight.Type = D3DLIGHT_FORCE_DWORD;
	m_pLight.Diffuse.r = 255;
	m_pLight.Diffuse.g = 255;
	m_pLight.Diffuse.b = 255;
	m_pLight.Diffuse.a = 255;
	m_pLight.Specular.r = 100;
	m_pLight.Specular.g = 100;
	m_pLight.Specular.b = 100;
	m_pLight.Specular.a = 255;
	m_pLight.Ambient.r = 150;
	m_pLight.Ambient.g = 150;
	m_pLight.Ambient.b = 150;
	m_pLight.Ambient.a = 255;
	iIndice = _iIndice;
	m_D3DDevice = _D3DDevice;
	bActive = false;
}
void Light :: SetIndice(short _iIndice)
{
	iIndice = _iIndice;
}
void Light :: SetDiffuse(uchr r, uchr g, uchr b, uchr a)
{
	m_pLight.Diffuse.r = r;
	m_pLight.Diffuse.g = g;
	m_pLight.Diffuse.b = b;
	m_pLight.Diffuse.a = a;
}
void Light :: SetSpecular(uchr r, uchr g, uchr b, uchr a)
{
	m_pLight.Specular.r = r;
	m_pLight.Specular.g = g;
	m_pLight.Specular.b = b;
	m_pLight.Specular.a = a;
}
void Light :: SetAmbient(uchr r, uchr g, uchr b, uchr a)
{
	m_pLight.Ambient.r = r;
	m_pLight.Ambient.g = g;
	m_pLight.Ambient.b = b;
	m_pLight.Ambient.a = a;
}
void Light :: SetOn()
{
	bActive = true;
}
void Light :: SetOff()
{
	bActive = false;
}
bool Light :: IsLightOn()
{
	return bActive;
}

