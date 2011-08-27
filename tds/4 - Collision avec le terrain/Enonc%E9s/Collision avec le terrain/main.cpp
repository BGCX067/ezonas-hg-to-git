#include "Game.h"

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//Game::GetSingleton()->Render();
    switch(msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:
            Game::GetSingleton()->Render();
            ValidateRect(hWnd, NULL);
            return 0;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lCmd, INT i)
{
	Game *G = Game::GetSingleton(); 

	G->SetName(L"TD Collision avec le terrain");

	G->wWinMain(MsgProc, hInst, hPrev, lCmd, i);
}