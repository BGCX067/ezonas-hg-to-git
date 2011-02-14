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
    Camera * m_pCamera; // this now is the current camera
	CameraMode m_CameraMode;

    Object*     m_pTarget;

    // Singleton
    CameraManager();
	CameraManager(CameraMode _cameraMode);

	// quats
	Camera * camera_from;
	Camera * camera_to;
	//Camera * camera_transit;

	void Transit();
	bool IsTransiting;
	void PositionRotationLerp();

	float current_factor, interp_step;

	D3DXVECTOR3 pos_from, pos_to, pos_transit;
	D3DXMATRIX mat_from, mat_to, mat_transit;
	D3DXQUATERNION quat_from, quat_to, quat_transit;
};
#endif // PC1__cameraManagerH__