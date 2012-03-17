
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "resource.h"
#include "Configuration.h"

//Proptypes
int loadXFile(LPWSTR);
void DetermineConfiguration(HWND hWnd, WPARAM wParam);


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device

LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials
Configuration		g_config;

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice. Since we are now
    // using more complex geometry, we will create a device with a zbuffer.
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    // Create the D3DDevice
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                      D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                                      &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
    }

    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xff707070 );


    return S_OK;
}

void SetupRenderState()
{
	// Set shading mode
	g_pd3dDevice->SetRenderState( D3DRS_SHADEMODE, g_config.shadeMode );

	//Set fill mode
	g_pd3dDevice->SetRenderState( D3DRS_FILLMODE, g_config.fillMode );

}


//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Load the mesh and build the material and texture arrays
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{  
    return loadXFile(L"..\\bigship1.x");
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{


    if( g_pMeshMaterials != NULL )
        delete[] g_pMeshMaterials;

    if( g_pMesh != NULL )
        g_pMesh->Release();

    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: SetupLights()
// Desc: Sets up the lights and materials for the scene.
//-----------------------------------------------------------------------------
VOID SetupLights()
{
    // Set up a material. The material here just has the diffuse and ambient
    // colors set to yellow. Note that only one material can be used at a time.
    D3DMATERIAL9 mtrl;
    ZeroMemory( &mtrl, sizeof( D3DMATERIAL9 ) );
    mtrl.Diffuse.r = 1.0f;
    mtrl.Diffuse.g = 1.0f;
    mtrl.Diffuse.b = 1.0f;
    mtrl.Diffuse.a = 1.0f;
    g_pd3dDevice->SetMaterial( &mtrl );

    // Set up a white, directional light, with an oscillating direction.
    // Note that many lights may be active at a time (but each one slows down
    // the rendering of our scene). However, here we are just using one. Also,
    // we need to set the D3DRS_LIGHTING renderstate to enable lighting
    D3DXVECTOR3 vecDirOrPos;
    D3DLIGHT9 light;
    ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	light.Type = g_config.lightType;

    light.Range = 15.0f;

	if (g_config.lightType == D3DLIGHT_POINT){
		D3DXMATRIXA16 rotateYMatrix;
		D3DXMatrixRotationY(&rotateYMatrix, g_config.lightAngle);
		vecDirOrPos = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
		D3DXVec3TransformNormal(&vecDirOrPos, &vecDirOrPos, &rotateYMatrix);
		light.Position = vecDirOrPos;
		light.Attenuation0 = 0.6f;
		light.Attenuation1 = 0.1f;
		light.Attenuation2 = 0.0f;
	}

	light.Diffuse.r = (0x00FF0000 & g_config.lightColour) == 0 ? 0.0f:1.0f;
    light.Diffuse.g = (0x0000FF00 & g_config.lightColour) == 0 ? 0.0f:1.0f;
    light.Diffuse.b = (0x000000FF & g_config.lightColour) == 0 ? 0.0f:1.0f;

	if (g_config.lightType == D3DLIGHT_DIRECTIONAL){
		D3DXMATRIXA16 rotateYMatrix;
		D3DXMatrixRotationY(&rotateYMatrix, g_config.lightAngle);
		vecDirOrPos = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
		D3DXVec3TransformNormal(&vecDirOrPos, &vecDirOrPos, &rotateYMatrix);
		D3DXVec3Normalize( ( D3DXVECTOR3* )&light.Direction, &vecDirOrPos );
	}
    g_pd3dDevice->SetLight( 0, &light );
    g_pd3dDevice->LightEnable( 0, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
	D3DXMATRIXA16 matRotY;
	D3DXMatrixRotationY(&matWorld, g_config.xAngle);
	D3DXMatrixRotationX(&matRotY, g_config.yAngle);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotY);
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix.
    D3DXVECTOR3 vEyePt( 0.0f, 0.0f,-30.0f );
    D3DXVECTOR3 vLookatPt( 0.0f, 0.0f, 0.0f );
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

	//Set up the projection matrix
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f );
	
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{

    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                         D3DCOLOR_XRGB( 50, 50, 50 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
		SetupRenderState();
		SetupLights();
        // Setup the world, view, and projection matrices
        SetupMatrices();

        // Meshes are divided into subsets, one for each material. Render them in
        // a loop
        for( DWORD i = 0; i < g_dwNumMaterials; i++ )
        {
            // Set the material and texture for this subset
            g_pd3dDevice->SetMaterial( &g_pMeshMaterials[i] );

            // Draw the mesh subset
            g_pMesh->DrawSubset( i );
        }

        // End the scene
        g_pd3dDevice->EndScene();
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}


void handleRotation(LPARAM lParam)
{
	float x = LOWORD(lParam);
	float y = HIWORD(lParam);

	if (g_config.rotateType == ROTATE_MODEL)
	{
		g_config.xAngle -= (x - g_config.x) / 50;
		g_config.yAngle -= (y - g_config.y) / 50;

	}
	else if(g_config.rotateType == ROTATE_LIGHT)
	{
		g_config.lightAngle -= (x - g_config.x) / 50;
	}

	Render();
	g_config.x = x;	
	g_config.y = y;
}

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static BOOL mouseDown = false;

    switch( msg )
    {
		case WM_COMMAND:
			DetermineConfiguration(hWnd, wParam);
			return 0;
		case WM_PAINT:
			BeginPaint(hWnd, NULL);
			EndPaint(hWnd, NULL);
			Render();
			return 0;
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
		case WM_MOUSEMOVE:
			if (mouseDown){
				handleRotation(lParam);
			}
			return 0;
		case WM_LBUTTONDOWN:
			mouseDown = true;
			g_config.x = LOWORD(lParam);
			g_config.y = HIWORD(lParam);	
			
			return 0;

		case WM_LBUTTONUP:
			mouseDown = false;
			return 0;

    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}


//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );
	//Load our Icon
	HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1));

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), hIcon, NULL, NULL, L"ass2Menu",
        L"ass2", NULL
    };
    RegisterClassEx( &wc );

	//Load our menu
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));	

    // Create the application's window
    HWND hWnd = CreateWindow( L"ass2", L"Willy's X-Viewer",
                              WS_OVERLAPPEDWINDOW, 100, 100, 700, 600,
							  NULL, hMenu, wc.hInstance, NULL );

    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Create the scene geometry
        if( SUCCEEDED( InitGeometry() ) )
        {
            // Show the window
            ShowWindow( hWnd, SW_SHOWDEFAULT );
            UpdateWindow( hWnd );

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
			Render();
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                
            }
        }
    }

    UnregisterClass( L"ass2", wc.hInstance );
    return 0;
}

void resetPosition()
{
	g_config.xAngle = 0.0f;
	g_config.yAngle = 0.0f;
}

/********************************************************************
Function Name: 	DetermineMenuProps
Purpose: 		Determine the menu properties based on the wParam of the 
				event
In parameters:	props - properties structure to modify
				wParam - the event code to analyze
Version: 		1.0
Author: 		William Collins
**********************************************************************/
void DetermineConfiguration(HWND hWnd, WPARAM wParam)
{
	switch (LOWORD(wParam))
	{
		case ID_ABOUT_ABOUTX:
			MessageBoxW( hWnd, TEXT("X-Viewer - William Collins\nGame Programming - Winter 2012"), TEXT("About"), MB_OK);
			return;
		case ID_FILLMODE_POINT:
			g_config.fillMode = D3DFILL_POINT;
			break;
		case ID_FILLMODE_SOLID:
			g_config.fillMode = D3DFILL_SOLID;
			break;
		case ID_FILLMODE_WIREFRAME:
			g_config.fillMode = D3DFILL_WIREFRAME;
			break;
		case ID_LIGHTS_DIRECTIONALLIGHT:
			g_config.lightType = D3DLIGHT_DIRECTIONAL;
			break;
		case ID_LIGHTS_POINTLIGHT:
			g_config.lightType = D3DLIGHT_POINT;
			break;
		case ID_SHADEMODE_FLAT:
			g_config.shadeMode = D3DSHADE_FLAT;
			break;
		case ID_SHADEMODE_GOURAUD:
			g_config.shadeMode = D3DSHADE_GOURAUD;
			break;
		case ID_SHADEMODE_PHONG:
			g_config.shadeMode = D3DSHADE_PHONG;
			break;
		case ID_MODEL_BIGSHIP:
			loadXFile( L"..\\bigship1.x" );
			break;
		case ID_MODEL_SPACESTATION:
			loadXFile( L"..\\space station 5.x" );
			break;
		case ID_MODEL_CAR:
			loadXFile( L"..\\car.x" );
			break;
		case ID_LIGHTCOLOURS_BLUE:
			g_config.lightColour = 0xFF0000FF;
			break;
		case ID_LIGHTCOLOURS_GREEN:
			g_config.lightColour = 0xFF00FF00;
			break;
		case ID_LIGHTCOLOURS_RED:
			g_config.lightColour = 0xFFFF0000;
			break;
		case ID_LIGHTCOLOURS_WHITE:
			g_config.lightColour = 0xFFFFFFFF;
			break;
		case ID_ROTATINGOBJECT_MODEL:
			g_config.rotateType = ROTATE_MODEL;
			break;
		case ID_ROTATINGOBJECT_LIGHT:
			g_config.rotateType = ROTATE_LIGHT;
			break;
		default:
			break;

	}
	Render();
}

int loadXFile(LPWSTR name)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;
	resetPosition();

	if (g_pMesh != NULL){
		g_pMesh->Release();
	}

    // Load the mesh from the specified file
    if( FAILED( D3DXLoadMeshFromX( name, D3DXMESH_SYSTEMMEM,
                                   g_pd3dDevice, NULL,
                                   &pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
                                   &g_pMesh ) ) )
    {
		MessageBox( NULL, L"Could not find mesh", L"ass2.exe", MB_OK );
        return E_FAIL;
    }

    // We need to extract the material properties and texture names from the 
    // pD3DXMtrlBuffer
    D3DXMATERIAL* d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBuffer->GetBufferPointer();

	//Make sure to free up resources
	if (g_pMeshMaterials != NULL){
		delete []g_pMeshMaterials;
	}

    g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
    if( g_pMeshMaterials == NULL )
        return E_OUTOFMEMORY;

    for( DWORD i = 0; i < g_dwNumMaterials; i++ )
    {
        // Copy the material
        g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;
        
    }

    // Done with the material buffer
    pD3DXMtrlBuffer->Release();

	return S_OK;
}



