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

Game * Game :: GetSingleton(){static Game _; return & _;}
Game :: ~ Game (){UnregisterClass ("D3D Tutorial", wc.hInstance);}
Game :: Game(int _buffer_w, int _buffer_h):
	buffer_w(_buffer_w),
	buffer_h(_buffer_h)
{
    WNDCLASSEX _wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "D3D Tutorial", NULL };
	wc = _wc;
	RegisterClassEx (&wc);

    // Create the application's window
    hWnd = CreateWindow ("D3D Tutorial", "D3D Tutorial 01: CreateDevice", 
                              WS_OVERLAPPEDWINDOW, 100, 100,
							  buffer_w, buffer_h,
                              GetDesktopWindow(), NULL,
							  wc.hInstance, NULL);
InitD3D(hWnd);
}

HRESULT Game :: InitD3D (HWND hWnd)
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if (NULL ==  (g_pD3D = Direct3DCreate9 (D3D_SDK_VERSION) ) ) 
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp; 
    ZeroMemory (&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed               = TRUE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferWidth        = buffer_w;
    d3dpp.BackBufferHeight       = buffer_h;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

	if (FAILED (g_pD3D->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice) ) ) 
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}
VOID Game :: Cleanup()
{
    if (g_pd3dDevice != NULL)  g_pd3dDevice->Release();
    if (g_pD3D != NULL) g_pD3D->Release();
}
VOID Game :: Render()
{
    if (NULL == g_pd3dDevice) 
        return;

    // Clear the backbuffer to a blue color
    g_pd3dDevice->Clear (0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,255), 1.0f, 0);
    
    // Begin the scene
    if (SUCCEEDED (g_pd3dDevice->BeginScene()) ) 
    {
        // Rendering of scene objects can happen here
		sprite -> Display();
        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present (NULL, NULL, NULL, NULL);
}
void Game :: Go()
{
    ShowWindow (hWnd, SW_SHOWDEFAULT);
    UpdateWindow (hWnd);
    MSG msg; 
    while (GetMessage (&msg, NULL, 0, 0) ) 
    {
        TranslateMessage (&msg);
        DispatchMessage (&msg);
    }
}