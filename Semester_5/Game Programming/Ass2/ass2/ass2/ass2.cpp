
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include "resource.h"

//Proptypes
int loadXFile(LPWSTR);


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device

LPD3DXMESH          g_pMesh = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterials = NULL; // Materials for our mesh
DWORD               g_dwNumMaterials = 0L;   // Number of mesh materials

float x1 = 0;
float x2 = 0;

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
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    return S_OK;
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
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // Set up world matrix
    D3DXMATRIXA16 matWorld;
	D3DXMatrixRotationY(&matWorld, (x2 - x1) / 100);
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );

    // Set up our view matrix.
    D3DXVECTOR3 vEyePt( 0.0f, 3.0f,-5.0f );
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
                         D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
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




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static BOOL mouseDown = false;

    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
		case WM_MOUSEMOVE:
			if (mouseDown){
				x2 = LOWORD(lParam);
				Render();
				x1 = x2;			
			}
			return 0;
		case WM_LBUTTONDOWN:
			mouseDown = true;
			x1 = LOWORD(lParam);
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

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, L"ass2Menu",
        L"ass2", NULL
    };
    RegisterClassEx( &wc );

	//Load our menu
	HMENU hMenu = LoadMenu(hInst, MAKEINTRESOURCE(IDR_MENU1));

    // Create the application's window
    HWND hWnd = CreateWindow( L"ass2", L"Willy's X-Viewer",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
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

int loadXFile(LPWSTR name)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

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



