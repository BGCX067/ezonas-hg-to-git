#include "MeshLoader.h"
MeshLoader::MeshLoader(LPDIRECT3DDEVICE9 _Device, LPCWSTR _szName)
{
	HRESULT hr = 0;

	m_D3DDevice = _Device ;

	//
	// Load the XFile data.
	//
	ID3DXBuffer* adjBuffer  = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls   = 0;

	hr = D3DXLoadMeshFromX(  
		_szName,
		D3DXMESH_MANAGED,
		_Device,
		&adjBuffer,
		&mtrlBuffer,
		0,
		&numMtrls,
		&m_Mesh);

	if(FAILED(hr))
        
	{
		::MessageBox(0, L"D3DXLoadMeshFromX() - FAILED", 0, 0);
	}
    
	//
	// Extract the materials, load textures.
	//

	if( mtrlBuffer != 0 && numMtrls != 0 )
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for(int i = 0; i < (int) numMtrls; i++)
		{
			// the MatD3D property doesn't have an ambient value set
			// when its loaded, so set it now:
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;

			// save the ith material
			Mtrls.push_back( mtrls[i].MatD3D );

			// check if the ith material has an associative texture
			if( mtrls[i].pTextureFilename != 0 )
			{
				// yes, load the texture for the ith subset
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFile(
					_Device,
					(LPCWSTR)mtrls[i].pTextureFilename,
					&tex);

				// save the loaded texture
				Textures.push_back( tex );
			}
			else
			{
				// no texture for the ith subset
				Textures.push_back( 0 );
			}
		}
	}

	//
	// Optimize the mesh.
	//

	hr = m_Mesh->OptimizeInplace(		
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT  |
		D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(),
		0, 0, 0);

	if(FAILED(hr))
	{
		::MessageBox(0, L"OptimizeInplace() - FAILED", 0, 0);
	}
}
MeshLoader::~MeshLoader()
{    
}
void MeshLoader::Display()
{
	for(int i = 0; i < (int) Mtrls.size(); i++)
	{
		m_D3DDevice->SetMaterial( &Mtrls[i] );
		m_D3DDevice->SetTexture(0, Textures[i]);
		m_Mesh->DrawSubset(i);
	}	
}
