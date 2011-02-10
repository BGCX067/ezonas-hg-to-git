#ifndef __SHADER_H__
#define __SHADER_H__

#include "d3dx9.h"
#include "d3d9.h"

class Shader
{
	private :

		ID3DXEffect * m_pEffect;
		UINT m_uiPass;
		LPDIRECT3DDEVICE9 m_D3DDevice;

	public :

		Shader(LPDIRECT3DDEVICE9 _Device, LPCWSTR _szName);
		~Shader() {};

		// Set effect parameters functions
		void SetBool(D3DXHANDLE _hParameter, const bool &_b);
		void SetBoolArray(D3DXHANDLE _hParameter, const BOOL * _pb, UINT _Count);
		void SetFloat(D3DXHANDLE _hParameter, const float &_f);
		void SetFloatArray(D3DXHANDLE _hParameter, const float * _pf, UINT _Count);
		void SetInt(D3DXHANDLE _hParameter, const int &_i);
		void SetIntArray(D3DXHANDLE _hParameter, const int * _pi, UINT _Count);
		void SetMatrix(D3DXHANDLE _hParameter, const D3DXMATRIX * _mMatrix);
		void SetMatrixArray(D3DXHANDLE _hParameter, const D3DXMATRIX * _pMatrix, UINT _Count);
		void SetString(D3DXHANDLE _hParameter, LPCSTR _szString);
		void SetTexture(D3DXHANDLE _hParameter, LPDIRECT3DBASETEXTURE9 _pTexture);

		// Apply effect functions
		UINT Begin();
		void BeginPass(UINT _pass);
		void EndPass();
		void End();


};

#endif // __SHADER_H__