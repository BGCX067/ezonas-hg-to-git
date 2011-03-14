#ifndef __ObjectH__
#define __ObjectH__

#include <d3dx9.h>
#include <string>
#include <vector>

using namespace std;

class Object
{
public:
    Object();
    ~Object();

    virtual void GetMatrix (D3DXMATRIX* _m);
    virtual void GetPos (D3DXVECTOR3* _pos);
    virtual void GetLook (D3DXVECTOR3* _look);
    virtual void GetUp (D3DXVECTOR3* _up);
    virtual bool Display(IDirect3DDevice9* Device, float timeDelta);
    virtual void Update(float timeDelta);

protected:

    D3DXMATRIX  World;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_pos;

};
#endif // __ObjectH__