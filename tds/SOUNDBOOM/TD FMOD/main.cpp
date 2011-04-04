#include "Game.h"

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

	//launch frame
	Game::GetSingleton()->Render();

    switch( msg )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            return 0;

			
		case WM_KEYDOWN:
			if ( wParam == VK_ESCAPE )
			{
				::DestroyWindow(hWnd);
			}      
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE hPrev, LPSTR lCmd, INT i)
{
	Game *pGame = Game::GetSingleton() ; 

	pGame->SetName(L"TD FMOD") ;

	pGame->wWinMain(MsgProc, hInst, hPrev, lCmd, i) ;
}