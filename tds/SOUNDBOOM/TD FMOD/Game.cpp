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
	iState = IDLE;
	
	m_szWindowName = L"TD FMOD" ;

	flKeypress = false;
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

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
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
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

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

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void Game::Render()
{
    if( NULL == m_D3DDevice )
        return;

    // Clear the backbuffer to a blue color
    m_D3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( m_iR, m_iG, m_iB ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( m_D3DDevice->BeginScene() ) )
    {
        // Rendering of scene objects can happen here

		switch ( iState )
		{
			case IDLE :
				{
					m_Sprite->Display();
					break;
				}

			case OPENING :
				{
					m_Sprite2->Display();
					break;
				}

			case CLOSEIRIS :
				{
					m_Sprite3->Display();
					break;
				}

			case OPENIRIS :
				{
					m_Sprite2->Display();
					break;
				}

			case CLOSING :
				{
					m_Sprite->Display();
					break;
				}

			default :
				{
					m_Sprite->Display();
					break;
				}
		};

        // End the scene
        m_D3DDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    m_D3DDevice->Present( NULL, NULL, NULL, NULL );

	//streams commands
	if ( ::GetAsyncKeyState( VK_DOWN ) & 0x8000f )
	{
		//pause stream
	}

	if ( ::GetAsyncKeyState( VK_RIGHT ) & 0x8000f )
	{
		//play stream
	}

	if ( ::GetAsyncKeyState( VK_LEFT ) & 0x8000f )
	{
		//stop stream
	}

	//updating scene status
	if ( ( ::GetAsyncKeyState( VK_UP ) & 0x8000f ) && ( ! flKeypress ) )
	{
		iState = ( iState + 1 ) % NUMOFSTATE;

		flKeypress = true;

		switch ( iState )
		{

			case OPENING :
				{
					break;
				}

			case CLOSEIRIS :
				{
					break;
				}

			case OPENIRIS :
				{
					break;
				}

			case CLOSING :
				{
					break;
				}

			default :
				{
					break;
				}
		};
	}
	else
	{
		flKeypress = false;
	}

	//updating stargate position
	if ( ::GetAsyncKeyState( VK_NUMPAD6 ) & 0x8000f )
	{		
		m_Sprite->Move( -10.0f , 0.0f );
		m_Sprite2->Move( -10.0f , 0.0f );
		m_Sprite3->Move( -10.0f , 0.0f );

		//update 3D position of sound 
	}
	else if ( ::GetAsyncKeyState( VK_NUMPAD4 ) & 0x8000f )
	{	
		m_Sprite->Move( 10.0f , 0.0f );
		m_Sprite2->Move( 10.0f , 0.0f );
		m_Sprite3->Move( 10.0f , 0.0f );
		
		//update 3D position of sound 
	}
	else
	{	
		//update sound 
	}

}


//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
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
        L"TD FMOD", NULL
    };

    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"TD FMOD", m_szWindowName,
                              WS_OVERLAPPEDWINDOW, m_iX, m_iY, m_iL, m_iH,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
		
		//loading of object can append here 
		m_Sprite = new Sprite(m_D3DDevice) ;
		m_Sprite->SetTexture(L"stargateclose.png") ;
		m_Sprite->Move( 300.0f , 150.0f );
		
		m_Sprite2 = new Sprite(m_D3DDevice) ;
		m_Sprite2->SetTexture(L"stargateopen.png") ;
		m_Sprite2->Move( 300.0f , 150.0f );
		
		m_Sprite3 = new Sprite(m_D3DDevice) ;
		m_Sprite3->SetTexture(L"stargateiris.png") ;
		m_Sprite3->Move( 300.0f , 150.0f );

		//Initiate Sound/SoundManager there

        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Enter the message loop
        MSG msg;
        while( GetMessage( &msg, NULL, 0, 0 ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
    }

    UnregisterClass( L"TD FMOD", wc.hInstance );

    return 0;
}
