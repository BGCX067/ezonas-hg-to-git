/**
 * CameraManager implémentation
 * 
 * @author  Colin Bruneau
 * @since   15/02/2006 09:22:00
 * @version 1.0
 */

#include "CameraManager.h"
#include "cameradebug.h"
#include "camerafirstperson.h"
#include "camerathirdperson.h"
#include <assert.h>

static CameraManager* pCameraManager = NULL;

CameraManager::CameraManager()
{
	m_CameraMode = CAMNONE;
    m_pCamera = new Camera();
    m_pTarget = NULL;
	IsTransiting = false;
	interp_step = 0.01f;
	current_factor = 0.0f;
}
CameraManager::CameraManager(CameraMode _CameraMode)
{
	setCameraMode(_CameraMode);
	IsTransiting = false;
	interp_step = 0.1;
}
CameraManager::~CameraManager()
{
    if (pCameraManager)
    {
        delete pCameraManager;
    }
    if (m_pCamera)
    {
        delete m_pCamera;
    }
}
void CameraManager::getPosition(D3DXVECTOR3* _pos)
{
    m_pCamera->getPosition(_pos);
}
void CameraManager::setPosition(D3DXVECTOR3* _pos)
{
    m_pCamera->setPosition(_pos);
}
void CameraManager::getRight(D3DXVECTOR3* _right)
{
    m_pCamera->getRight(_right);
}
void CameraManager::getUp(D3DXVECTOR3* _up)
{
    m_pCamera->getUp(_up);
}
void CameraManager::getLook(D3DXVECTOR3* _look)
{
    m_pCamera->getLook(_look);
}
void CameraManager::getViewMatrix(D3DXMATRIX* V)
{
    m_pCamera->getViewMatrix(V);
}
void CameraManager::getCameraMode(CameraMode& _cameraMode)
{
    _cameraMode = m_CameraMode;
}
void CameraManager::setCameraMode(CameraMode _CameraMode)
{
    D3DXVECTOR3 vZero(0.0f, 0.0f, 0.0f);
	m_CameraMode = _CameraMode;

    Camera* pCamera = m_pCamera;

    switch (_CameraMode)
    {
    case CAMDEBUG:
        m_pCamera = new CameraDebug(*pCamera);
		//Transit(* pCamera, * m_pCamera);
        delete pCamera;
        break;
    case CAMFIRST:
        m_pCamera = new CameraFirstPerson(*pCamera);
        m_pCamera->setPosition(&vZero);
        delete pCamera;
        break;
    case CAMTHIRD:
        m_pCamera = new CameraThirdPerson(*pCamera);
        m_pCamera->setPosition(&vZero);
        m_pCamera->setTarget(m_pTarget);
        m_pCamera->setOffset(30.0f, 20.0f);
        delete pCamera;
        break;
    default:
        break;
    }
}
CameraManager* CameraManager::getCameraManager()
{
    if (pCameraManager==NULL)
    {
        pCameraManager = new CameraManager();
    }
    return pCameraManager;
}
void CameraManager::update(float timeDelta)
{
    if (m_pCamera) m_pCamera->update(timeDelta);
}
void CameraManager::setTarget(Object* _target)
{
    m_pTarget = _target;
    m_pCamera->setTarget(m_pTarget);
}
void Transit(Camera & cam1, Camera & cam2)
{
	if(IsTransiting == false)
	{
		IsTransiting = true;
		current_factor = 0.0f;
	}

	if(current_factor <= 1.0f)
	{
		current_factor += interp_step;
	// positions
		cam1.getPosition(& v1);
		cam2.getPosition(& v2);
		PositionLerp(v1, v2, v3, current_factor);
		m_pCamera -> setPosition(& v3);

	//rotation
		// converting mats to quats
		cam1.getViewMatrix(& m1);
		cam2.getViewMatrix(& m2);
		D3DXQuaternionRotationMatrix(& q1, & m1);
		D3DXQuaternionRotationMatrix(& q2, & m2);
		
		// interpolating
		D3DXQuaternionSlerp(& q3, & q2, & q1, current_factor);
		// converting back quats to mats
		D3DXMatrixRotationQuaternion(& m3, & q3);
		// setting the current cam
		m_pCamera -> S
	}
	else
	{
		IsTransiting = false;
	}
}
void PositionLerp // cam1 is old cam pos, cam2 is the new cam pos
	(D3DXVECTOR3 & cam1,
		D3DXVECTOR3 & cam2,
		D3DXVECTOR3 & result,
		float factor)
{
	result.x = factor * (cam2.x - cam1.x);
	result.y = factor * (cam2.y - cam1.y);
	result.z = factor * (cam2.z - cam1.z);
}
