// TDX1.cpp : définit le point d'entrée pour l'application console.
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	return 0;
//	Game * game = Game :: GetSingleton();
//
//	system ("PAUSE");
//}

#include "stdafx.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_KEYDOWN:
		{
			switch( wParam )
			{
				case VK_ESCAPE:
					PostQuitMessage(0);
					break;
			}
		}
        break;

        case WM_DESTROY:
            Game :: GetSingleton() -> Cleanup();
            PostQuitMessage( 0 );
            return 0;

        case WM_PAINT:
            Game :: GetSingleton() -> Render();
            ValidateRect( hWnd, NULL );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE a, LPSTR b, INT c)
{
	Game * game = Game :: GetSingleton();
	Sprite spr(game ->getdevice());
	game->mySprite=&spr;
	game -> wWinMain (hInst, a, b, c, MsgProc);
	
	//spr.Display();

}


