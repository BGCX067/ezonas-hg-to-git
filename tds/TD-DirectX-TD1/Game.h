#include "stdafx.h"
class Game
{
public:
	static Game * GetSingleton();
		Sprite * mySprite;

	HRESULT InitD3D (HWND hWnd );
	VOID Render();
	INT WINAPI wWinMain (HINSTANCE hInst, HINSTANCE, LPSTR, INT, WNDPROC);
	VOID Cleanup();
	LPDIRECT3D9 getd3d() { return g_pD3D; };
	LPDIRECT3DDEVICE9 getdevice() { return g_pd3dDevice; }
protected:
	Game();
// Used to create the D3DDevice
	LPDIRECT3D9 g_pD3D;
// Our rendering device
	LPDIRECT3DDEVICE9 g_pd3dDevice;


};