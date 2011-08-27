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
}

CameraManager::CameraManager(CameraMode _CameraMode)
{
	setCameraMode(_CameraMode);
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
    D3DXVECTOR3 vZero(0.0f, 40.0f, -100.0f);
	m_CameraMode = _CameraMode;

    Camera* pCamera = m_pCamera;

    switch (_CameraMode)
    {
    case CAMDEBUG:
        m_pCamera = new CameraDebug(*pCamera);
        m_pCamera->setPosition(&vZero);
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
    if (m_pCamera)
        m_pCamera->update(timeDelta);
}

void CameraManager::setTarget(Object* _target)
{
    m_pTarget = _target;
    m_pCamera->setTarget(m_pTarget);
}