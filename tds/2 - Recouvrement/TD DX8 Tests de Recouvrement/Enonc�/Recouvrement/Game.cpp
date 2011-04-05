#include "Game.h"

LPDIRECT3D9         Game::m_D3D = NULL; 
LPDIRECT3DDEVICE9   Game::m_D3DDevice = NULL; 

Game :: Game()
{
	m_iX = 0;
	m_iY = 0; 
	m_iL = 800;
	m_iH = 600; 
	m_iR = 0;
	m_iG = 0;
	m_iB = 0;
	
	m_szWindowName = L"Application";

	m_iRenderVolume = 0;
	m_iRenderVolume2 = 0;
	m_iRenderVolume3 = 0;
	m_flKeyDown = false;
	m_flKeyDown2 = false;
	m_flKeyDown3 = false;
	m_fRotation = 0.0f;
	m_fTranslation = 100.0f;
	collides = false;

	BLUE = D3DXCOLOR(D3DCOLOR_XRGB( 0,   0, 255));
	BLACK = D3DXCOLOR(D3DCOLOR_XRGB( 0,   0,   0));
	RED = D3DXCOLOR(D3DCOLOR_XRGB( 200,   0,   0));
	blu.Ambient = BLUE;
	blu.Diffuse = BLUE ;
	blu.Emissive = BLACK ;
	blu.Power = 2.0f;
	blu.Diffuse.a = 0.30f; // 30% opacity
	blu.Specular = BLUE;

	red.Ambient = RED;
	red.Diffuse = RED ;
	red.Emissive = BLACK ;
	red.Power = 2.0f;
	red.Diffuse.a = 0.30f; // 30% opacity
	red.Specular = RED;



}
Game :: ~ Game()
{
	//release le device
	SafeRelease(m_D3DDevice);

	//release l'interface DX9
    SafeRelease(m_D3D);
}
Game* Game :: GetSingleton()
{
	static Game InstanceUnique;

	return &InstanceUnique;
}
HRESULT Game :: InitD3D(HWND hWnd)
{
    // Create the D3D object, which is needed to create the D3DDevice.
    if(NULL == (m_D3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Most parameters are
    // zeroed out. We set Windowed to TRUE, since we want to do D3D in a
    // window, and then set the SwapEffect to "discard", which is the most
    // efficient method of presenting the back buffer to the display.  And 
    // we request a back buffer format that matches the current desktop display 
    // format.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
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
    if(FAILED(m_D3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &m_D3DDevice)))
    {
        return E_FAIL;
    }

    // Device state would normally be set here
	InitialiseLights();
	SetupCamera();

    return S_OK;
}
void Game :: InitialiseLights()
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
	m_D3DDevice->SetLight(0, &d3dLight);

	//Enable our point light in position (index) 0
	m_D3DDevice->LightEnable(0, TRUE);

	//Turn on lighting
    m_D3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//Set ambient light level
	m_D3DDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(60, 60, 60));
}
void Game :: SetupCamera()
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
void Game :: Render()
{
	//D3DXMATRIX M, N, World;
		radius_sum_squared =
			(m_BSphere2->m_fRadius + m_BSphere->m_fRadius)
			* (m_BSphere2->m_fRadius + m_BSphere->m_fRadius);

    if(NULL == m_D3DDevice) return;
	CheckCollisions();
	m_D3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	m_D3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_D3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

    // Clear the backbuffer to a blue color
	m_D3DDevice->Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(m_iR, m_iG, m_iB), 1.0f, 0);
	
    // Begin the scene
    if(SUCCEEDED(m_D3DDevice->BeginScene()))
    {
		switch(m_iRenderVolume3)
		{
		case 0:
			m_iRenderVolume = 0;
			m_iRenderVolume2 = 0;
			break;

		case 1: // sphere box
			m_iRenderVolume = 0;
			m_iRenderVolume2 = 1;
			break;
	
		case 2: // aabb
			m_iRenderVolume = 1;
			m_iRenderVolume2 = 1;
			break;
	
		case 3: // obb
			m_iRenderVolume = 2;
			m_iRenderVolume2 = 2;
			break;
		}
	    // Rendering of scene objects can happen here

		// Rotation & translation
		D3DXMatrixIdentity(&M);
		D3DXMatrixRotationY(&M, m_fRotation);
		M._43 = m_fTranslation;
		m_D3DDevice->SetTransform(D3DTS_WORLD, &M);
		World = M;

		// Display the mesh
		m_Mesh->Display();

		// Set the material
	
		if (collides)
			m_D3DDevice->SetMaterial(&blu);
		else
			m_D3DDevice->SetMaterial(&red);
		m_D3DDevice->SetTexture(0, 0); // disable texture

		// Initial world
		D3DXMatrixIdentity(&M);
		m_D3DDevice->SetTransform(D3DTS_WORLD, &M);

		// Display the bounding volume
		if(m_iRenderVolume == 0) { m_BSphere->Update(World); m_BSphere->Render(); }
		if(m_iRenderVolume == 1) { m_OBB->Update(World); m_OBB->Render(); }
		if(m_iRenderVolume == 2) { m_AABB->Update(World); m_AABB->Render();	}


		/////////////////////////////////////////////////////////////////////////
		// Rotation & translation
		D3DXMatrixIdentity(&N);
		m_D3DDevice->SetTransform(D3DTS_WORLD, &N);
		World = N;

		// Display the mesh
		m_Mesh2->Display();

		// Set the material
	
		if (collides)
			m_D3DDevice->SetMaterial(&blu);
		else
			m_D3DDevice->SetMaterial(&red);
		m_D3DDevice->SetTexture(0, 0); // disable texture

		// Initial world
		D3DXMatrixIdentity(&N);
		m_D3DDevice->SetTransform(D3DTS_WORLD, &N);

		// Display the bounding volume
		if(m_iRenderVolume2 == 0)	{ m_BSphere2->Update(World); m_BSphere2->Render();}
		if(m_iRenderVolume2 == 1)	{ m_OBB2->Update(World); m_OBB2->Render();}
		if(m_iRenderVolume2 == 2) 	{ m_AABB2->Update(World); m_AABB2->Render();}
	
		// End the scene
        m_D3DDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    m_D3DDevice->Present(NULL, NULL, NULL, NULL);


	if(::GetAsyncKeyState(VK_SPACE) && m_flKeyDown == false)
	{ m_flKeyDown = true; m_iRenderVolume ++; if(m_iRenderVolume > 2) m_iRenderVolume = 0; }
	if(!::GetAsyncKeyState(VK_SPACE)) m_flKeyDown = false;

	if(::GetAsyncKeyState('B') && m_flKeyDown2 == false)
	{ m_flKeyDown2 = true; m_iRenderVolume2 ++; if(m_iRenderVolume2 > 2) m_iRenderVolume2 = 0; }
	if(!::GetAsyncKeyState('B')) m_flKeyDown2 = false;

	if(::GetAsyncKeyState('N') && m_flKeyDown3 == false)
	{ m_flKeyDown3 = true; m_iRenderVolume3 ++; if(m_iRenderVolume3 > 3) m_iRenderVolume3 = 0; }
	if(!::GetAsyncKeyState('N')) m_flKeyDown3 = false;


	if(::GetAsyncKeyState(VK_ESCAPE)) exit(0xb00b);

	if(::GetAsyncKeyState(VK_LEFT)) 
	{ m_fRotation -= 0.1f;if(m_fRotation < -3.14f)m_fRotation = 3.14f; }

	if(::GetAsyncKeyState(VK_RIGHT)) 
	{ m_fRotation += 0.1f;if(m_fRotation > 3.14f)m_fRotation = -3.14f; }

	if(::GetAsyncKeyState(VK_UP)) m_fTranslation += 1.0f;
	if(::GetAsyncKeyState(VK_DOWN)) m_fTranslation -= 1.0f;

}
INT WINAPI Game::wWinMain(WNDPROC _MsgProc, HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof(WNDCLASSEX), 
		CS_CLASSDC, 
		_MsgProc, 
		0L, 
		0L,
        GetModuleHandle(NULL), 
		NULL, NULL, NULL, NULL,
        L"D3D Initiation", NULL
    };

    RegisterClassEx(&wc);

    // Create the application's window
    HWND hWnd = CreateWindow(L"D3D Initiation", m_szWindowName,
                              WS_OVERLAPPEDWINDOW, m_iX, m_iY, m_iL, m_iH,
                              NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if(SUCCEEDED(InitD3D(hWnd)))
    {
		//loading of object can append here 
		m_Mesh = new MeshLoader(m_D3DDevice, L"bigship1.x");
		m_BSphere = new BoundingSphere(m_D3DDevice, m_Mesh->GetMesh());
		m_OBB = new OBB(m_D3DDevice, m_Mesh->GetMesh());
		m_AABB = new AABB(m_D3DDevice, m_Mesh->GetMesh());

		m_Mesh2 = new MeshLoader(m_D3DDevice, L"bigship1.x");
		m_BSphere2 = new BoundingSphere(m_D3DDevice, m_Mesh2->GetMesh());
		m_OBB2 = new OBB(m_D3DDevice, m_Mesh2->GetMesh());
		m_AABB2 = new AABB(m_D3DDevice, m_Mesh2->GetMesh());
        // Show the window
        ShowWindow(hWnd, SW_SHOWDEFAULT);
        UpdateWindow(hWnd);
        
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

    UnregisterClass(L"D3D Initiation", wc.hInstance);

    return 0;
}

void Game :: CheckCollisions()
{
	switch(m_iRenderVolume3)
	{
		
	case 0: //sphere sphere
		vect = D3DXVECTOR3(m_BSphere->m_vCenter - m_BSphere2->m_vCenter);
		if (D3DXVec3LengthSq(&vect) < radius_sum_squared)
			collides = true;
		else
			collides = false;
		break;
	
	case 1: // sphere box
		cout << std :: endl;
		break;
	
	case 2: // aabb

		break;
	
	case 3: // obb

		break;

	default:
		break;

	}
}