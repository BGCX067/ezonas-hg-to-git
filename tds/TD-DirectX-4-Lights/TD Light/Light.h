#ifndef LIGHT__H
#define LIGHT__H

#include <d3dx9.h>
#include "helper.h"
typedef unsigned char uchr;

class Light
{
	protected :

		D3DLIGHT9 m_pLight;
		LPDIRECT3DDEVICE9 m_D3DDevice;
		short iIndice;
		bool bActive;

	public :
		D3DLIGHT9 * GetLight () {return & m_pLight;}
		Light(LPDIRECT3DDEVICE9 _D3DDevice, short _iIndice);
		~Light();
		void SetIndice(short _iIndice);
		void SetDiffuse(uchr r, uchr g, uchr b, uchr a);
		void SetSpecular(uchr r, uchr g, uchr b, uchr a);
		void SetAmbient(uchr r, uchr g, uchr b, uchr a);
		void SetOn();
		void SetOff();
		bool IsLightOn();

		// void SetDirection();
		// void SetPosition();
		// void SetAttenuation();
		// void SetRange();
		// void SetCone();
};
class PointLight: public Light
{
public:
	PointLight(LPDIRECT3DDEVICE9 _D3DDevice, short _iIndice):
		Light(_D3DDevice, _iIndice)
	{
		m_pLight.Type = D3DLIGHT_POINT;
		SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}
		void SetPosition(D3DXVECTOR3 _pos) { pos = _pos;}
protected:
	D3DVECTOR pos;
};
class SpotLight: public Light
{
public:
	SpotLight(LPDIRECT3DDEVICE9 _D3DDevice, short _iIndice):
		Light(_D3DDevice, _iIndice)
	{
		m_pLight.Type = D3DLIGHT_SPOT;
		SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		SetDirection(D3DXVECTOR3(0.0f, -1.0f, 0.0f));
		SetCone(10.0f);
	}
	void SetPosition(D3DXVECTOR3 _pos) { m_pLight.Position = _pos;}
	void SetDirection(D3DXVECTOR3 _dir) { m_pLight.Direction = _dir;}
	void SetCone(float _cone_angle)
	{ m_pLight.Phi = _cone_angle; m_pLight.Theta = _cone_angle; }
protected:
	float cone_angle;
};
/*typedef struct D3DLIGHT9 {
  D3DLIGHTTYPE  Type;
  D3DCOLORVALUE Diffuse;
  D3DCOLORVALUE Specular;
  D3DCOLORVALUE Ambient;
  D3DVECTOR     Position;
  D3DVECTOR     Direction;
  float         Range;
  float         Falloff;
  float         Attenuation0;
  float         Attenuation1;
  float         Attenuation2;
  float         Theta;
  float         Phi;
} D3DLIGHT9, *LPD3DLIGHT;
typedef enum _D3DLIGHTTYPE {
    D3DLIGHT_POINT          = 1,
    D3DLIGHT_SPOT           = 2,
    D3DLIGHT_DIRECTIONAL    = 3,
    D3DLIGHT_FORCE_DWORD    = 0x7fffffff, //force 32-bit size enum 
} D3DLIGHTTYPE;
*/
class DirectionnalLight: public Light
{
public:
	DirectionnalLight(LPDIRECT3DDEVICE9 _D3DDevice, short _iIndice):
		Light(_D3DDevice, _iIndice)
	{
		m_pLight.Type = D3DLIGHT_DIRECTIONAL; 
		SetDirection(D3DXVECTOR3(-45.f, -45.f, -45.f));
	}
	void SetDirection(D3DXVECTOR3 _dir) { m_pLight.Direction = _dir;}
protected:
	
};

#endif //LIGHT__H
