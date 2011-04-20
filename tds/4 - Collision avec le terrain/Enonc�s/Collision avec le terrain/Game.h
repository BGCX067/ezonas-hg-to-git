#ifndef GAME__H
#define GAME__H

#include <d3d9.h>
#include <d3dx9.h>
#include "Helper.h"

#include "Cuboid.h"
#include "Terrain.h"

class Game
{
		int m_iX, m_iY, m_iL, m_iH;
		int m_iR, m_iG, m_iB;
		LPCTSTR m_szWindowName;
		Game();

		static LPDIRECT3D9         m_D3D; // Used to create the D3DDevice
		static LPDIRECT3DDEVICE9   m_D3DDevice; // Our rendering device

		CCuboid *m_Cube;
		CTerrain *m_Terrain;

	public :

		static Game* GetSingleton();

		inline void SetX(const int &_iX) {m_iX = _iX;}; // X position of de window
		inline void SetY(const int &_iY) {m_iY = _iY;}; // Y position of the window
		inline void SetL(const int &_iL) {m_iL = _iL;}; // L size of the window
		inline void SetH(const int &_iH) {m_iH = _iH;}; // H size of the window
		inline void SetR(const int &_iR) {m_iR = _iR;}; // Red color of the window
		inline void SetG(const int &_iG) {m_iG = _iG;}; // Green color of the window
		inline void SetB(const int &_iB) {m_iB = _iB;}; // Blue color of the window
		inline void SetName(const LPCTSTR &_Name) {m_szWindowName = _Name;}; // Name of the window

		inline int GetX() {return m_iX;};
		inline int GetY() {return m_iY;};
		inline int GetL() {return m_iL;};
		inline int GetH() {return m_iH;};
		inline int GetR() {return m_iR;};
		inline int GetG() {return m_iG;};
		inline int GetB() {return m_iB;};
		inline LPCTSTR GetName() {return m_szWindowName;};
		
		INT WINAPI wWinMain(WNDPROC _MsgProc, HINSTANCE hInst, HINSTANCE, LPSTR, INT);
		HRESULT InitD3D(HWND hWnd);
		void InitialiseLights();
		void SetupCamera();
		void Render();

		virtual ~Game();
};

#endif // GAME__H