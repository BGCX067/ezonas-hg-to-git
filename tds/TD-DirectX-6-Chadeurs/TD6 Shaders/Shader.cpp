#include "Shader.h"

Shader :: Shader(LPDIRECT3DDEVICE9 _Device, LPCWSTR _szName) 
{
}

void Shader :: SetBool(D3DXHANDLE _hParameter, const bool &_b) 
{
}

void Shader :: SetBoolArray(D3DXHANDLE _hParameter, const BOOL * _pb, UINT _Count) 
{
}

void Shader :: SetFloat(D3DXHANDLE _hParameter, const float &_f) 
{
}

void Shader :: SetFloatArray(D3DXHANDLE _hParameter, const float * _pf, UINT _Count) 
{
}

void Shader :: SetInt(D3DXHANDLE _hParameter, const int &_i) 
{
}

void Shader :: SetIntArray(D3DXHANDLE _hParameter, const int * _pi, UINT _Count) 
{
}

void Shader :: SetMatrix(D3DXHANDLE _hParameter, const D3DXMATRIX * _mMatrix) 
{
}

void Shader :: SetMatrixArray(D3DXHANDLE _hParameter, const D3DXMATRIX * _pMatrix, UINT _Count) 
{
}

void Shader :: SetString(D3DXHANDLE _hParameter, LPCSTR _szString) 
{
}

void Shader :: SetTexture(D3DXHANDLE _hParameter, LPDIRECT3DBASETEXTURE9 _pTexture) 
{
}

UINT Shader :: Begin() 
{
	return 0;
}

void Shader :: BeginPass(UINT _pass) 
{
}

void Shader :: EndPass() 
{
}

void Shader :: End() 
{
}
