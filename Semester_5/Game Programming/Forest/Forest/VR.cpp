//-----------------------------------------------------------------------------
// File: VR.cpp
// A tutorial-level example of VR.
// A Virtual Reality to use as a base application for assignment #3, built on the code in Tut06_Meshes
// Doesn't contain protective code to deal with a lost device.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include <mmsystem.h>
#include <d3dx9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <math.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx10d.lib")
#pragma comment(lib,"d3dx9d.lib")
#pragma comment(lib,"dxerr.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"Kernel32.lib")

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9         g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9   g_pd3dDevice = NULL; // Our rendering device


LPD3DXMESH          g_pMeshSkyBox = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterialsSkyBox = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9* g_pMeshTexturesSkyBox = NULL; // Textures for our mesh
DWORD               g_dwNumMaterialsSkyBox = 0L;   // Number of mesh materials


LPD3DXMESH          g_pMeshTerrain = NULL; // Our mesh object in sysmem
D3DMATERIAL9*       g_pMeshMaterialsTerrain = NULL; // Materials for our mesh
LPDIRECT3DTEXTURE9* g_pMeshTexturesTerrain = NULL; // Textures for our mesh
DWORD               g_dwNumMaterialsTerrain = 0L;   // Number of mesh materials

#define g_numTrees 500

// Need global access to the eye direction used by the callback to sort trees
D3DXVECTOR3 g_vDir;

// Simple function to define "hilliness" for terrain
inline FLOAT HeightField( FLOAT x, FLOAT z )
{
    return 9*(cosf(x/20+0.2f)*cosf(z/15-0.2f)+1.0f);	// 0 <= HeightField <= 18
}

// Custom vertex type for the trees
struct TREEVERTEX
{
    D3DXVECTOR3 p;      // Vertex position
    DWORD       color;  // Vertex color
    FLOAT       tu, tv; // Vertex texture coordinates
    static const DWORD FVF;
};
const DWORD TREEVERTEX::FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

// Tree textures to use
TCHAR* g_strTreeTextures[] =
{
    TEXT("Tree02S.dds"),
    TEXT("Tree35S.dds"),
    TEXT("Tree01S.dds"),
};

#define NUMTREETEXTURES 3

//-----------------------------------------------------------------------------
// Name: Tree
// Desc: Simple structure to hold data for rendering a tree
//-----------------------------------------------------------------------------
struct Tree
{
    TREEVERTEX  v[4];           // Four corners of billboard quad
    D3DXVECTOR3 vPos;           // Origin of tree
    DWORD       dwTreeTexture;  // Which texture map to use
    DWORD       dwOffset;       // Offset into vertex buffer of tree's vertices
};

LPD3DXMESH     g_pTerrain;           // Terrain object
LPD3DXMESH     g_pSkyBox;            // Skybox background object

LPDIRECT3DVERTEXBUFFER9		g_pTreeVB;							// Vertex buffer for rendering a tree
LPDIRECT3DTEXTURE9			g_pTreeTextures[NUMTREETEXTURES];	// Tree images
D3DXMATRIXA16				g_matBillboardMatrix;				// Used for billboard orientation
Tree						g_Trees[g_numTrees];				// Array of tree info

D3DXVECTOR3					g_vEyePt;							// Camera position

 // Main objects used for creating and rendering the 3D scene
    D3DCAPS9          g_d3dCaps;           // Caps for the device
    // Variables for timing
    float				g_fTime;             // Current time in seconds



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
    if( FAILED( g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,  D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice ) ) )
           return E_FAIL;
   
    // Turn on the zbuffer
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );

    // Turn on ambient lighting 
    g_pd3dDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: IsTreePositionValid
// Desc: Verifies that the tree at the given index is sufficiently spaced
//       from the other trees. If trees are placed too closely, one tree
//       can quickly pop in front of the other as the camera angle changes.
//-----------------------------------------------------------------------------
bool IsTreePositionValid( DWORD iTree )
{
    FLOAT x = g_Trees[iTree].vPos.x;
    FLOAT z = g_Trees[iTree].vPos.z;

    for( DWORD i=0; i < iTree; i++ )
    {
        double fDeltaX = fabs( x - g_Trees[i].vPos.x );
        double fDeltaZ = fabs( z - g_Trees[i].vPos.z );

        if( 3.0 > pow( fDeltaX, 2 ) + pow( fDeltaZ, 2 ) )
            return false;
	}
	return true;
}
	


//-----------------------------------------------------------------------------
// Name: SetUpTrees()
// Desc: Called during initial app startup, this function performs all the
//       permanent initialization.
//-----------------------------------------------------------------------------
HRESULT SetUpTrees()
{
    // Initialize the tree data
    for( WORD i=0; i<g_numTrees; i++ )
    {
        do
        {
            // Position the trees randomly
            FLOAT fTheta  = 2.0f*D3DX_PI*(FLOAT)rand()/RAND_MAX;
            FLOAT fRadius = 25.0f + 55.0f * (FLOAT)rand()/RAND_MAX;
            g_Trees[i].vPos.x  = fRadius * sinf(fTheta);
            g_Trees[i].vPos.z  = fRadius * cosf(fTheta);
            g_Trees[i].vPos.y  = HeightField( g_Trees[i].vPos.x, g_Trees[i].vPos.z );
        }
        while( !IsTreePositionValid( i ) );

        // Size the trees randomly
        FLOAT fWidth  = 1.4f + 0.42f * (FLOAT)(rand()-rand())/RAND_MAX;
        FLOAT fHeight = 2.0f + 0.6f * (FLOAT)(rand()-rand())/RAND_MAX;

        // Each tree is a random color between red and green
        DWORD r = (255-190) + (DWORD)(190*(FLOAT)(rand())/RAND_MAX);
        DWORD g = (255-190) + (DWORD)(190*(FLOAT)(rand())/RAND_MAX);
        DWORD b = 0;
        DWORD dwColor = 0xff000000 + (r<<16) + (g<<8) + (b<<0);

        g_Trees[i].v[0].p     = D3DXVECTOR3(-fWidth, 0*fHeight, 0.0f );
        g_Trees[i].v[0].color = dwColor;
        g_Trees[i].v[0].tu    = 0.0f;   g_Trees[i].v[0].tv = 1.0f;
        g_Trees[i].v[1].p     = D3DXVECTOR3(-fWidth, 2*fHeight, 0.0f  );
        g_Trees[i].v[1].color = dwColor;
        g_Trees[i].v[1].tu    = 0.0f;   g_Trees[i].v[1].tv = 0.0f;
        g_Trees[i].v[2].p     = D3DXVECTOR3( fWidth, 0*fHeight, 0.0f  );
        g_Trees[i].v[2].color = dwColor;
        g_Trees[i].v[2].tu    = 1.0f;   g_Trees[i].v[2].tv = 1.0f;
        g_Trees[i].v[3].p     = D3DXVECTOR3( fWidth, 2*fHeight, 0.0f  );
        g_Trees[i].v[3].color = dwColor;
        g_Trees[i].v[3].tu    = 1.0f;   g_Trees[i].v[3].tv = 0.0f;

        // Pick a random texture for the tree
        g_Trees[i].dwTreeTexture = (DWORD)( ( NUMTREETEXTURES * rand() ) / (FLOAT)RAND_MAX );
    }

return S_OK;
}


//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Load the mesh and build the material and texture arrays
//-----------------------------------------------------------------------------
HRESULT InitGeometry()
{
	LPD3DXBUFFER  pD3DXMtrlBufferTerrain, pD3DXMtrlBufferSkyBox ;
    D3DXMATERIAL* d3dxMaterials;
	 
	 // Load terrain
    D3DXLoadMeshFromX( TEXT("terrain.x"), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBufferTerrain, NULL, &g_dwNumMaterialsTerrain, &g_pMeshTerrain ) ;
	 // We need to extract the material properties and texture names 
   
    d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBufferTerrain->GetBufferPointer();
    g_pMeshMaterialsTerrain = new D3DMATERIAL9[g_dwNumMaterialsTerrain];
    if( g_pMeshMaterialsTerrain == NULL )
        return E_OUTOFMEMORY;
    g_pMeshTexturesTerrain = new LPDIRECT3DTEXTURE9[g_dwNumMaterialsTerrain];
    if( g_pMeshTexturesTerrain == NULL )
        return E_OUTOFMEMORY;

    for( DWORD i = 0; i < g_dwNumMaterialsTerrain; i++ )
    {
        // Copy the material
        g_pMeshMaterialsTerrain[i] = d3dxMaterials[i].MatD3D;

        // Set the ambient color for the material (D3DX does not do this)
        g_pMeshMaterialsTerrain[i].Ambient = g_pMeshMaterialsTerrain[i].Diffuse;

        g_pMeshTexturesTerrain[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL &&lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
        {
           // Create the texture
           D3DXCreateTextureFromFileA( g_pd3dDevice,  d3dxMaterials[i].pTextureFilename,  &g_pMeshTexturesTerrain[i] );
        }
    }

    // Done with the material buffer
    pD3DXMtrlBufferTerrain->Release();
	
	// Load Skybox	
	D3DXLoadMeshFromX( TEXT("SkyBox.x"), D3DXMESH_SYSTEMMEM, g_pd3dDevice, NULL, &pD3DXMtrlBufferSkyBox, NULL, &g_dwNumMaterialsSkyBox, &g_pMeshSkyBox );
	
	 // We need to extract the material properties and texture names from the pD3DXMtrlBuffer
    d3dxMaterials = ( D3DXMATERIAL* )pD3DXMtrlBufferSkyBox->GetBufferPointer();
    g_pMeshMaterialsSkyBox = new D3DMATERIAL9[g_dwNumMaterialsSkyBox];
    if( g_pMeshMaterialsSkyBox == NULL )
        return E_OUTOFMEMORY;
    g_pMeshTexturesSkyBox = new LPDIRECT3DTEXTURE9[g_dwNumMaterialsSkyBox];	// unreleased
    if( g_pMeshTexturesSkyBox == NULL )
        return E_OUTOFMEMORY;

	for( DWORD i = 0; i < g_dwNumMaterialsSkyBox; i++ )
	{
        g_pMeshMaterialsSkyBox[i] = d3dxMaterials[i].MatD3D;	// Copy the material
        g_pMeshMaterialsSkyBox[i].Ambient = g_pMeshMaterialsSkyBox[i].Diffuse;// Set the ambient color for the material (D3DX does not do this)
        g_pMeshTexturesSkyBox[i] = NULL;
        if( d3dxMaterials[i].pTextureFilename != NULL && lstrlenA( d3dxMaterials[i].pTextureFilename ) > 0 )
		{
            D3DXCreateTextureFromFileA( g_pd3dDevice,  d3dxMaterials[i].pTextureFilename,  &g_pMeshTexturesSkyBox[i] );// Create the texture
		}
	}
	pD3DXMtrlBufferSkyBox->Release();
	
	
	// Add some "hilliness" to the terrain
    LPDIRECT3DVERTEXBUFFER9 pVB;
	
	if( SUCCEEDED( g_pMeshTerrain->GetVertexBuffer( &pVB ) ) )
    {
        struct VERTEX { FLOAT x,y,z,tu,tv; };
        VERTEX* pVertices;
        DWORD   dwNumVertices = g_pMeshTerrain->GetNumVertices();

        pVB->Lock( 0, 0, (void**)&pVertices, 0 );

        for( DWORD i=0; i<dwNumVertices; i++ )
            pVertices[i].y = HeightField( pVertices[i].x, pVertices[i].z );

        pVB->Unlock();
        pVB->Release();
    }
	
	HRESULT hr;
	
	// Create the tree textures
    for( DWORD i=0; i<NUMTREETEXTURES; i++ )
    {
        if( FAILED( hr =  D3DXCreateTextureFromFile( g_pd3dDevice, g_strTreeTextures[i],  &g_pTreeTextures[i] ) ) )
			return hr;
    }

    // Create a quad for rendering each tree
    if( FAILED( hr = g_pd3dDevice->CreateVertexBuffer( g_numTrees*4*sizeof(TREEVERTEX), D3DUSAGE_WRITEONLY, TREEVERTEX::FVF,  D3DPOOL_MANAGED, &g_pTreeVB, NULL ) ) )
    {
        return hr;
    }
	
	SetUpTrees();
	
	// Copy tree mesh data into vertexbuffer
    TREEVERTEX* v;
    g_pTreeVB->Lock( 0, 0, (void**)&v, 0 );

    INT iTree;
    DWORD dwOffset = 0;
    for( iTree = 0; iTree < g_numTrees; iTree++ )
    {
        memcpy( &v[dwOffset], g_Trees[iTree].v, 4*sizeof(TREEVERTEX) );
        g_Trees[iTree].dwOffset = dwOffset;
	    dwOffset += 4;
    }

    g_pTreeVB->Unlock();

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	// Release terrain and free heap allocation
	if( g_pMeshMaterialsTerrain != NULL )
        delete[] g_pMeshMaterialsTerrain;

    if( g_pMeshTexturesTerrain )
    {
        for( DWORD i = 0; i < g_dwNumMaterialsTerrain; i++ )
        {
            if( g_pMeshTexturesTerrain[i] )
                g_pMeshTexturesTerrain[i]->Release();
        }
        
		delete []g_pMeshTexturesTerrain;
    }
	
    if( g_pMeshTerrain != NULL )
        g_pMeshTerrain->Release();
	
	
	// Release Skybox and free heap allocation
	if( g_pMeshMaterialsSkyBox != NULL )
        delete[] g_pMeshMaterialsSkyBox;

    if( g_pMeshTexturesSkyBox )
    {
        for( DWORD i = 0; i < g_dwNumMaterialsSkyBox; i++ )
        {
            if( g_pMeshTexturesSkyBox[i] )
                g_pMeshTexturesSkyBox[i]->Release();
        }

      delete[] g_pMeshTexturesSkyBox;	
    }
	
	if( g_pMeshSkyBox != NULL )
        g_pMeshSkyBox->Release();

	
	for( DWORD i = 0; i < NUMTREETEXTURES; i++ )
    {
            if( g_pTreeTextures[i] )
                g_pTreeTextures[i]->Release();
    }

	    
	if( g_pTreeVB != NULL)
		g_pTreeVB->Release();


    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();

    if( g_pD3D != NULL )
        g_pD3D->Release();
}

//-----------------------------------------------------------------------------
// Name: TreeSortCB()
// Desc: Callback function for sorting trees in back-to-front order
//-----------------------------------------------------------------------------
int __cdecl TreeSortCB( const VOID* arg1, const VOID* arg2 )
{
    Tree* p1 = (Tree*)arg1;
    Tree* p2 = (Tree*)arg2;
    
    FLOAT d1 = p1->vPos.x * g_vDir.x + p1->vPos.z * g_vDir.z;
    FLOAT d2 = p2->vPos.x * g_vDir.x + p2->vPos.z * g_vDir.z;
    if (d1 < d2)
        return +1;

    return -1;
}

//-----------------------------------------------------------------------------
// Name: DrawTrees()
// Desc:
//-----------------------------------------------------------------------------
HRESULT DrawTrees()
{
    // Set diffuse blending for alpha set in vertices.
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_SRCBLEND,  D3DBLEND_SRCALPHA );
    g_pd3dDevice->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

    // Enable alpha testing (skips pixels with less than a certain alpha.)
    if( g_d3dCaps.AlphaCmpCaps & D3DPCMPCAPS_GREATEREQUAL )
    {
        g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHAREF,        0x08 );
        g_pd3dDevice->SetRenderState( D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
    }

    // Loop through and render all trees
    g_pd3dDevice->SetStreamSource( 0, g_pTreeVB, 0, sizeof(TREEVERTEX) );
    g_pd3dDevice->SetFVF( TREEVERTEX::FVF );
    for( DWORD i=0; i<g_numTrees; i++ )
    {
        // Quick culling for trees behind the camera
        // This calculates the tree position relative to the camera, and
        // projects that vector against the camera's direction vector. A
        // negative dot product indicates a non-visible tree.
        if( 0 > ( g_Trees[i].vPos.x - g_vEyePt.x ) * g_vDir.x + 
                ( g_Trees[i].vPos.z - g_vEyePt.z ) * g_vDir.z )
        {
            break;
        }
        
        // Set the tree texture
        g_pd3dDevice->SetTexture( 0, g_pTreeTextures[g_Trees[i].dwTreeTexture] );

        // Translate the billboard into place
        g_matBillboardMatrix._41 = g_Trees[i].vPos.x;
        g_matBillboardMatrix._42 = g_Trees[i].vPos.y;
        g_matBillboardMatrix._43 = g_Trees[i].vPos.z;
        g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_matBillboardMatrix );

        // Render the billboard
        g_pd3dDevice->DrawPrimitive( D3DPT_TRIANGLESTRIP, g_Trees[i].dwOffset, 2 );
		//MessageBoxPrintfA("billboard","Tree %d",i);
    }

    // Restore state
    D3DXMATRIXA16  matWorld;
    D3DXMatrixIdentity( &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHATESTENABLE,    FALSE );
    g_pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,   FALSE );

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices()
{
    // Set up world matrix
	D3DXMATRIXA16  matWorld;
    D3DXMatrixIdentity( &matWorld );
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &matWorld );
	
    // For the projection matrix, we set up a perspective transform (which
    // transforms geometry from 3D view space to 2D viewport space, with
    // a perspective divide making objects smaller in the distance). To build
    // a perpsective transform, we need the field of view (1/4 pi is common),
    // the aspect ratio, and the near and far clipping planes (which define at
    // what distances geometry should be no longer be rendered).
    D3DXMATRIXA16 matProj;
    D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI / 4, 1.0f, 1.0f, 300.0f );
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	D3DXVECTOR3 vEyePt;
    D3DXVECTOR3 vLookatPt;
	D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
	g_fTime = timeGetTime()/1000.0;
	//QueryPerformanceFrequency(&g_fTimeInt);

	// Camera follows a elliptical orbit 5.0 above the terrain
    vEyePt.x = 30.0f*cosf( 0.4f * ( g_fTime ) );
    vEyePt.z = 80.0f*sinf( 0.4f * ( g_fTime ) );
    vEyePt.y = 5.0 + HeightField( vEyePt.x, vEyePt.z );

    vLookatPt.x = 30.0f*cosf( 0.4f * ( g_fTime + 0.2f ) );
    vLookatPt.z = 80.0f*sinf( 0.4f * ( g_fTime + 0.2f ) );
 	vLookatPt.y = vEyePt.y - 0.5f;
	
    // Set the app view matrix for normal viewing
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set up a rotation matrix to orient the billboard towards the camera.
    D3DXVECTOR3 vDir = vLookatPt - vEyePt;
    if( vDir.x > 0.0f )
        D3DXMatrixRotationY( &g_matBillboardMatrix, -atanf(vDir.z/vDir.x)+D3DX_PI/2 );
    else
        D3DXMatrixRotationY( &g_matBillboardMatrix, -atanf(vDir.z/vDir.x)-D3DX_PI/2 );
    g_vDir   = vDir;

    // Sort trees in back-to-front order
    qsort( g_Trees, g_numTrees, sizeof(Tree), TreeSortCB );

    // Store vectors used elsewhere
    g_vEyePt = vEyePt;

}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
    // Clear the backbuffer and the zbuffer
    g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );

	 // Set up the default texture states
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_DIFFUSE );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );
    g_pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSU,  D3DTADDRESS_CLAMP );
    g_pd3dDevice->SetSamplerState( 0, D3DSAMP_ADDRESSV,  D3DTADDRESS_CLAMP );

    g_pd3dDevice->SetRenderState( D3DRS_DITHERENABLE, TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_ZENABLE,      TRUE );
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING,     FALSE );

    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        // Setup the world, view, and projection matrices
        SetupMatrices();
	
		// Render Sky Box
		// Center view matrix for skybox and disable zbuffer
        D3DXMATRIXA16 matView, matViewSave;
        g_pd3dDevice->GetTransform( D3DTS_VIEW, &matViewSave );
        matView = matViewSave;
        matView._41 = 0.0f; matView._42 = -1.3f; matView._43 = 0.0f;
        g_pd3dDevice->SetTransform( D3DTS_VIEW,      &matView );
			
        g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, FALSE );
        // Some cards do not disable writing to Z when D3DRS_ZENABLE is FALSE. So do it explicitly
        g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
		// Meshes are divided into subsets, one for each material. Render them in a loop

		for( DWORD i = 0; i < g_dwNumMaterialsSkyBox; i++ )
        {
            // Set the material and texture for this subset
            g_pd3dDevice->SetMaterial( &g_pMeshMaterialsSkyBox[i] );
            g_pd3dDevice->SetTexture( 0, g_pMeshTexturesSkyBox[i] );

            // Draw the mesh subset
            g_pMeshSkyBox->DrawSubset( i );
        }
		// Restore the render states
            g_pd3dDevice->SetTransform( D3DTS_VIEW,      &matViewSave );
            g_pd3dDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
            g_pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE, TRUE);
		
		
		// Render terrain
		// Meshes are divided into subsets, one for each material. Render them in a loop
        for( DWORD i = 0; i < g_dwNumMaterialsTerrain; i++ )
        {
            // Set the material and texture for this subset
            g_pd3dDevice->SetMaterial( &g_pMeshMaterialsTerrain[i] );
            g_pd3dDevice->SetTexture( 0, g_pMeshTexturesTerrain[i] );

            // Draw the mesh subset
            g_pMeshTerrain->DrawSubset( i );
        }
		
		// Draw the trees
        DrawTrees();
				
        // End the scene
        g_pd3dDevice->EndScene();
    }
    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}



//-----------------------------------------------------------------------------
// Name: FrameMove()
// Desc: Called once per frame, the call is the entry point for animating
//       the scene.
//-----------------------------------------------------------------------------
HRESULT FrameMove()
{
    // Get the eye and lookat points from the camera's path
    D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
    D3DXVECTOR3 vEyePt;
    D3DXVECTOR3 vLookatPt;

    vEyePt.x = 30.0f*cosf( 0.8f * ( g_fTime ) );
    vEyePt.z = 30.0f*sinf( 0.8f * ( g_fTime ) );
    vEyePt.y = 4 + HeightField( vEyePt.x, vEyePt.z );

    vLookatPt.x = 30.0f*cosf( 0.8f * ( g_fTime + 0.5f ) );
    vLookatPt.z = 30.0f*sinf( 0.8f * ( g_fTime + 0.5f ) );
    vLookatPt.y = vEyePt.y - 1.0f;

    // Set the app view matrix for normal viewing
    D3DXMATRIXA16 matView;
    D3DXMatrixLookAtLH( &matView, &vEyePt, &vLookatPt, &vUpVec );
    g_pd3dDevice->SetTransform( D3DTS_VIEW, &matView );

    // Set up a rotation matrix to orient the billboard towards the camera.
    D3DXVECTOR3 vDir = vLookatPt - vEyePt;
    if( vDir.x > 0.0f )
        D3DXMatrixRotationY( &g_matBillboardMatrix, -atanf(vDir.z/vDir.x)+D3DX_PI/2 );
    else
        D3DXMatrixRotationY( &g_matBillboardMatrix, -atanf(vDir.z/vDir.x)-D3DX_PI/2 );
    g_vDir   = vDir;

    // Sort trees in back-to-front order
    qsort( g_Trees, g_numTrees, sizeof(Tree), TreeSortCB );

    // Store vectors used elsewhere
    g_vEyePt = vEyePt;

    return S_OK;
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
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
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        TEXT("VR"), NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( TEXT("VR"), TEXT("D3D VR"),
                              WS_OVERLAPPEDWINDOW, 100, 100, 1000, 700,
                              NULL, NULL, wc.hInstance, NULL );

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
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass( TEXT("VR"), wc.hInstance );
    return 0;
}



