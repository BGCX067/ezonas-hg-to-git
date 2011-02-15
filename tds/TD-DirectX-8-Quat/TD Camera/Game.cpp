#include "Game.h"

LPDIRECT3D9         Game::m_D3D = NULL ; 
LPDIRECT3DDEVICE9   Game::m_D3DDevice = NULL ; 

Game::Game()
{
	m_iX = 0 ;
	m_iY = 0 ; 
	m_iL = 800 ;
	m_iH = 600 ; 
	m_iR = 0 ;
	m_iG = 0 ;
	m_iB = 0 ;
	
	m_szWindowName = L"Application" ;

	m_flKeyDown = 0 ;
	CameraManager::getCameraManager()->setCameraMode(CAMDEBUG) ;

	m_fLastTimeGetTime = timeGetTime();
}
Game::~Game()
{
	//release le device
	SafeRelease( m_D3DDevice );

	//release l'interface DX9
    SafeRelease( m_D3D );
}
Game* Game::GetSingleton()
{
	static Game InstanceUnique ;

	return &InstanceUnique ;
}
HRESULT Game::InitD3D( HWND hWnd )
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if( NULL == ( m_D3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof(d3dpp) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;


    // Create the Direct3D device. Here we are using the default adapter (most
    // systems only have one, unless they have multiple graphics hardware cards
    // installed) and requesting the HAL (which is saying we want the hardware
    // device rather than a software one). Software vertex processing is 
    // specified since we know it will work on all cards. On cards that support 
    // hardware vertex processing, though, we would see a big performance gain 
    // by specifying hardware vertex processing.
    if( FAILED( m_D3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_D3DDevice ) ) )
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	InitialiseLights() ;
	SetupCamera() ;

    return S_OK;
}
void Game::InitialiseLights()
{	
	D3DLIGHT9 d3dLight;

	//Initialize the light structure.
	ZeroMemory(&d3dLight, sizeof(D3DLIGHT9));

	d3dLight.Type = D3DLIGHT_DIRECTIONAL;
	
	d3dLight.Diffuse.r = 1.0f;
	d3dLight.Diffuse.g = 1.0f;
	d3dLight.Diffuse.b = 1.0f;
	
	d3dLight.Ambient.r = 0.0f;
	d3dLight.Ambient.g = 0.0f;
	d3dLight.Ambient.b = 0.0f;
	
	d3dLight.Specular.r = 0.0f;
	d3dLight.Specular.g	= 0.0f;
	d3dLight.Specular.b	= 0.0f;

	d3dLight.Direction = D3DXVECTOR3(-1.0, -1.0, 0.0);

	//Assign the point light to our device in position (index) 0
	m_D3DDevice->SetLight(0, &d3dLight) ;

	//Enable our point light in position (index) 0
	m_D3DDevice->LightEnable(0, TRUE) ;

	//Turn on lighting
    m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE) ;

	//Set ambient light level
	m_D3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(60, 60, 60)) ;
}
void Game::SetupCamera()
{
	//Here we will setup the camera.
	//The camera has three settings: "Camera Position", "Look at Position" and "Up Direction"
	//We have set the following:
	//Camera Position:	(0, 200, -300)
	//Look at Position: (0, 0, 0)
	//Up direction:		Y-Axis.
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(0.0f, 50, -100),	//Camera Position
                                 &D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Look At Position
                                 &D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//Up Direction
    m_D3DDevice->SetTransform(D3DTS_VIEW, &matView);

	//Here we specify the field of view, aspect ration and near and far clipping planes.
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/4, 1.0f, 1.0f, 2000.0f);
    m_D3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
void Game::Render()
{
    if( NULL == m_D3DDevice )
        return;

	float fDt = (timeGetTime() - m_fLastTimeGetTime) * 0.001f;
	m_fLastTimeGetTime = timeGetTime();

	CameraManager* pCamManager = CameraManager::getCameraManager();
    CameraMode mode;
    pCamManager->getCameraMode(mode);

	if(mode == CAMTHIRD)
	{
		m_Cube->Update(fDt) ;
	}

    if( ::GetAsyncKeyState('M') && m_flKeyDown == 0)
    {
        m_flKeyDown = 1;
        if (mode == CAMDEBUG)
            mode = CAMFIRST;
        else if (mode == CAMFIRST)
            mode = CAMTHIRD;
        else if (mode == CAMTHIRD)
            mode = CAMDEBUG;
        pCamManager->setCameraMode(mode);
	}

	if(!::GetAsyncKeyState('M'))
    {
        m_flKeyDown = 0;
	}

	pCamManager->update(fDt) ;

	// Get view from the camera
	D3DXMATRIX mView ;
	pCamManager->getViewMatrix(&mView) ;
	m_D3DDevice->SetTransform(D3DTS_VIEW, &mView) ;

    // Clear the backbuffer to a blue color
	/*m_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(m_iR, m_iG, m_iB), 1.0f, 0);*/
	m_D3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00000000, 1.0f, 0);

    // Begin the scene
    if( SUCCEEDED( m_D3DDevice->BeginScene() ) )
    {
	    // Rendering of scene objects can happen here

		m_Cube->Display(m_D3DDevice, fDt) ;
		m_Cube->Render() ;

		D3DXMATRIX M ;
		D3DXMatrixIdentity(&M) ;
		m_D3DDevice->SetTransform(D3DTS_WORLD, &M) ;
		m_Terrain->Render() ;

		D3DXVECTOR3 a ;
		CameraManager::getCameraManager()->getPosition(&a) ;

        // End the scene
        m_D3DDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    m_D3DDevice->Present( NULL, NULL, NULL, NULL );
}
INT WINAPI Game::wWinMain(WNDPROC _MsgProc, HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc =
    {
		sizeof( WNDCLASSEX ), 
		CS_CLASSDC, 
		_MsgProc, 
		0L, 
		0L,
        GetModuleHandle( NULL ), 
		NULL, NULL, NULL, NULL,
        L"D3D Initiation", NULL
    };

    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"D3D Initiation", m_szWindowName,
                              WS_OVERLAPPEDWINDOW, m_iX, m_iY, m_iL, m_iH,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		//loading of object can append here 
		m_Cube = new CCuboid(m_D3DDevice, 0, 0, 0) ;
		m_Cube->SetTexture(L"cube.bmp") ;
		m_Terrain = new CTerrain(m_D3DDevice, 10, 10, 10,1) ;
		m_Terrain->SetTexture(L"Grass.bmp") ;

		CameraManager::getCameraManager()->setTarget(m_Cube) ;

        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );
        
        // Enter the message loop
		MSG msg; 
		BOOL fMessage;

		PeekMessage(&msg, NULL, 0U, 0U, PM_NOREMOVE);

		while(msg.message != WM_QUIT)
		{
			fMessage = PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE);

			if(fMessage)
			{
				//Process message
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else
			{
				//No message to process, so render the current scene
				Render();
			}
		}
	}

    UnregisterClass( L"D3D Initiation", wc.hInstance );

    return 0;
}