#include "stdafx.h"

Game * Game :: GetSingleton()
{
	static Game _;
	return & _;
}
Game :: Game():
	g_pd3dDevice(NULL),
	g_pD3D(NULL)
{}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
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
	d3dpp.BackBufferWidth        = 640;
    d3dpp.BackBufferHeight       = 480;
    d3dpp.BackBufferFormat       = D3DFMT_X8R8G8B8;
    d3dpp.PresentationInterval   = D3DPRESENT_INTERVAL_IMMEDIATE;

    
 //   d3dpp.Windowed = FALSE;
 //   d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
 //   d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if (FAILED (g_pD3D->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice) ) ) 
    {
        return E_FAIL;
    }

    // Device state would normally be set here

    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Game :: Cleanup()
{
    if (g_pd3dDevice != NULL) 
        g_pd3dDevice->Release();

    if (g_pD3D != NULL)
        g_pD3D->Release();
}
//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
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
		mySprite->Display();
        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present (NULL, NULL, NULL, NULL);
}
INT WINAPI Game :: wWinMain (HINSTANCE hInst, HINSTANCE, LPSTR, INT, WNDPROC d)
{
    // Register the window class
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, d, 0L, 0L, 
                      GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
                      "D3D Tutorial", NULL };
    RegisterClassEx (&wc);

    // Create the application's window
    HWND hWnd = CreateWindow ("D3D Tutorial", "D3D Tutorial 01: CreateDevice", 
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              GetDesktopWindow(), NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (SUCCEEDED (InitD3D (hWnd) ) ) 
    { 
        // Show the window
        ShowWindow (hWnd, SW_SHOWDEFAULT);
        UpdateWindow (hWnd);

        // Enter the message loop
        MSG msg; 
        while (GetMessage (&msg, NULL, 0, 0) ) 
        {
            TranslateMessage (&msg);
            DispatchMessage (&msg);
        }
    }

    UnregisterClass ("D3D Tutorial", wc.hInstance);
    return 0;
}
