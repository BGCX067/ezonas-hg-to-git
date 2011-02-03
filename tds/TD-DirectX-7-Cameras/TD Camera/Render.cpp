// #define AZERTY

#include "Game.h"
// OOOOOOOOOOOOOOOOOOOOOOOOOOOO  SetupCamera  OOOOOOOOOOOOOOOOOOOOOOOOOOOO
void Game :: SetupCamera()
{
	//Here we will setup the camera.
	//The camera has three settings: "Camera Position", "Look at Position" and "Up Direction"
	//We have set the following:
	//Camera Position:	(0, 200, -300)
	//Look at Position: (0, 0, 0)
	//Up direction:		Y-Axis.
    D3DXMATRIX matView;
    D3DXMatrixLookAtLH(&matView, & D3DXVECTOR3(0.0f, 50, -100),	//Camera Position
                                 & D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Look At Position
                                 & D3DXVECTOR3(0.0f, 1.0f, 0.0f));		//Up Direction
    m_D3DDevice -> SetTransform(D3DTS_VIEW, &matView);

	//Here we specify the field of view, aspect ration and near and far clipping planes.
    D3DXMATRIX matProj;
    D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI/2, 1.0f, 1.0f, 2000.0f);
    m_D3DDevice -> SetTransform(D3DTS_PROJECTION, &matProj);
}
// OOOOOOOOOOOOOOOOOOOOOOOOOOOO  Desc: Draws the scene  OOOOOOOOOOOOOOOOOOOOOOOOOOOO
void Game :: Render()
{
    if(NULL == m_D3DDevice)
        return;

    // Clear the backbuffer to a blue color
	m_D3DDevice -> Clear(0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(m_iR, m_iG, m_iB), 1.0f, 0);
	
    // Begin the scene
    if(SUCCEEDED(m_D3DDevice -> BeginScene()))
    {
	    // Rendering of scene objects can happen here

		D3DXMATRIX M;
		D3DXMatrixIdentity(&M);
		m_D3DDevice -> SetTransform(D3DTS_WORLD, &M);
		m_Terrain -> Render();

		D3DXMatrixIdentity(&M);
		m_D3DDevice -> SetTransform(D3DTS_WORLD, &M);
		m_Cube -> Render();

		// Get view from the camera
		D3DXMATRIX mView;
		cam_mgr.GetCamera() -> getViewMatrix(&mView);
		m_D3DDevice -> SetTransform(D3DTS_VIEW, &mView);

        // End the scene
        m_D3DDevice -> EndScene();
    }
    // Present the backbuffer contents to the display
    m_D3DDevice -> Present(NULL, NULL, NULL, NULL);
	cam_mgr.HandleKeys();
// #ifdef AZERTY
		// if( :: GetAsyncKeyState('Z') & 0x8000f) m_Camera -> walk(1.0f);
		// if( :: GetAsyncKeyState('Q') & 0x8000f) m_Camera -> strafe(-1.0f);
		// if( :: GetAsyncKeyState('N') & 0x8000f) m_Camera -> roll(0.1f);
		// if( :: GetAsyncKeyState('M') & 0x8000f) m_Camera -> roll(-0.1f);
// #else		
		// if( :: GetAsyncKeyState('W') & 0x8000f) m_Camera -> walk(1.0f);
		// if( :: GetAsyncKeyState('A') & 0x8000f) m_Camera -> strafe(-1.0f);
		// if( :: GetAsyncKeyState('Q') & 0x8000f) m_Camera -> roll(0.1f);
		// if( :: GetAsyncKeyState('E') & 0x8000f) m_Camera -> roll(-0.1f);
		
// #endif
		// if( :: GetAsyncKeyState('S') & 0x8000f) m_Camera -> walk(-1.0f);
		// if( :: GetAsyncKeyState('D') & 0x8000f) m_Camera -> strafe(1.0f);
		// if( :: GetAsyncKeyState('R') & 0x8000f) m_Camera -> fly(1.0f);
		// if( :: GetAsyncKeyState('F') & 0x8000f) m_Camera -> fly(-1.0f);
		// if( :: GetAsyncKeyState(VK_UP) & 0x8000f) m_Camera -> pitch(0.1f);
		// if( :: GetAsyncKeyState(VK_DOWN) & 0x8000f) m_Camera -> pitch(-0.1f);
		// if( :: GetAsyncKeyState(VK_LEFT) & 0x8000f) m_Camera -> yaw(-0.1f);
		// if( :: GetAsyncKeyState(VK_RIGHT) & 0x8000f) m_Camera -> yaw(0.1f);
}
