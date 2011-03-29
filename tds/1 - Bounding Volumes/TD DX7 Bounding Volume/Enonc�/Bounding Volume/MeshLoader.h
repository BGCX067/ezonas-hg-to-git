#ifndef __MESHLOADER_H__
#define __MESHLOADER_H__

#include <d3dx9.h>
#include <string>
#include <vector>

using namespace std;

class MeshLoader
{
public:
    MeshLoader(LPDIRECT3DDEVICE9 _Device, LPCWSTR _szName);
    ~MeshLoader();

    void Display();
	ID3DXMesh* GetMesh() {return m_Mesh ;} ;

protected:

	LPDIRECT3DDEVICE9				m_D3DDevice ;
    ID3DXMesh*                      m_Mesh ;
    std::vector<D3DMATERIAL9>       Mtrls ;
    std::vector<IDirect3DTexture9*> Textures ;
};
#endif // __MESHLOADER_H__