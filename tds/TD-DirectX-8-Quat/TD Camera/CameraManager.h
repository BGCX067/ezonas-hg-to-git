#ifndef PC1__cameraManagerH__
#define PC1__cameraManagerH__

#include <d3dx9.h>
#include "camera.h"
#include "object.h"

enum CameraMode { CAMNONE, CAMDEBUG, CAMFIRST, CAMTHIRD, CAMTOTALMODES };

class CameraManager
{
public:
	~CameraManager();
    static CameraManager* getCameraManager();
    void update(float timeDelta);
    void setTarget(Object* _target);

	void getViewMatrix(D3DXMATRIX* _V); 
	void getCameraMode(CameraMode& _cameraMode); 
	void setCameraMode(CameraMode _cameraMode); 
	void getPosition(D3DXVECTOR3* _pos); 
	void setPosition(D3DXVECTOR3* _pos); 

	void getRight(D3DXVECTOR3* _right);
	void getUp(D3DXVECTOR3* _up);
	void getLook(D3DXVECTOR3* _look);
private:
    Camera*     m_pCamera;
	CameraMode  m_CameraMode;

    Object*     m_pTarget;

    // Singleton
    CameraManager();
	CameraManager(CameraMode _cameraMode);

	// quats
	Camera * oldcamera;
	void Transit(Camera & cam1, Camera & cam2);
	bool IsTransiting;
	void PositionLerp
		(D3DXVECTOR3 & cam1,
			D3DXVECTOR3 & cam2,
			D3DXVECTOR3 & result,
			float factor);
	float current_factor;
	float interp_step;
	D3DXVECTOR3 v1, v2, v3;
	D3DXMATRIX m1, m2, m3;
	D3DXQUATERNION q1, q2, q3;
};
#endif // PC1__cameraManagerH__