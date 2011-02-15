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
		delete pCameraManager;
    if (m_pCamera)
        delete m_pCamera;
}
void CameraManager::getPosition(D3DXVECTOR3* _pos)			{m_pCamera->getPosition(_pos);}
void CameraManager::setPosition(D3DXVECTOR3* _pos)			{m_pCamera->setPosition(_pos);}
void CameraManager::getRight(D3DXVECTOR3* _right)			{m_pCamera->getRight(_right);}
void CameraManager::getUp(D3DXVECTOR3* _up)					{m_pCamera->getUp(_up);}
void CameraManager::getLook(D3DXVECTOR3* _look)				{m_pCamera->getLook(_look);}
void CameraManager::getViewMatrix(D3DXMATRIX* V)			{m_pCamera->getViewMatrix(V);}
void CameraManager::getCameraMode(CameraMode& _cameraMode)	{_cameraMode = m_CameraMode;}
void CameraManager::setCameraMode(CameraMode _CameraMode)
{
    D3DXVECTOR3 vZero(0.0f, 0.0f, 0.0f);
	m_CameraMode = _CameraMode;

	// saving the current camera to the from pointer
    camera_from = m_pCamera;

    switch (_CameraMode)
    {
    case CAMDEBUG:
        camera_to = new CameraDebug(* camera_from);
		IsTransiting = true; //////////////////////////////////////
		current_factor = 0.0f;
        break;

    case CAMFIRST:
        camera_to = new CameraFirstPerson(* camera_from);
        camera_to->setPosition(& vZero);
		IsTransiting = true; //////////////////////////////////////
		current_factor = 0.0f;
		break;

    case CAMTHIRD:
        m_pCamera = new CameraThirdPerson(* camera_from);
        camera_to->setPosition(& vZero);
        camera_to->setTarget(m_pTarget);
        camera_to->setOffset(30.0f, 20.0f);
		IsTransiting = true; //////////////////////////////////////
		current_factor = 0.0f;
		break;

    default:
        break;
    }
}
CameraManager* CameraManager::getCameraManager()
{
    if (pCameraManager==NULL)
        pCameraManager = new CameraManager();
    return pCameraManager;
}
void CameraManager::update(float timeDelta)
{
	if (m_pCamera) m_pCamera -> update(timeDelta);
	if (IsTransiting == true)
	{
		if(current_factor <= 1.0f)
		{
			PositionRotationLerp();
			current_factor += interp_step;
		}
		else
		{
			IsTransiting = false;
			delete camera_from;
			delete camera_to;
		}
	}
}
void CameraManager::setTarget(Object* _target)
{
    m_pTarget = _target;
    m_pCamera->setTarget(m_pTarget);
}
void CameraManager :: PositionRotationLerp ()
{
/* ############ POSITIONS ############ */
	// getting posistions
	if(from_done == false)
	{
		camera_from -> getPosition(& pos_from);
		camera_from -> getViewMatrix(& mat_from);
		D3DXQuaternionRotationMatrix(& quat_from, & mat_from);
		from_done = true;
	}

	camera_to -> getPosition(& pos_to);

	// interpolating positions
	pos_transit.x = current_factor * (pos_to.x - pos_from.x);
	pos_transit.y = current_factor * (pos_to.y - pos_from.y);
	pos_transit.z = current_factor * (pos_to.z - pos_from.z);

	// done, write it to the current cam
	m_pCamera -> setPosition(& pos_transit);

/* ############ ROTATIONS ############ */
	// converting mats to quats
	//camera_from -> getViewMatrix(& mat_from);
	camera_to -> getViewMatrix(& mat_to);

	// converting to quaternions
	// D3DXQuaternionRotationMatrix(& quat_from, & mat_from);
	D3DXQuaternionRotationMatrix(& quat_to, & mat_to);
		
	// interpolating quaternions
	D3DXQuaternionSlerp(& quat_transit, & quat_to, & quat_from, current_factor);

	// converting back quats to mats
	D3DXMatrixRotationQuaternion(& mat_transit, & quat_transit);

	// setting the current cam rotation matrix
	m_pCamera -> setViewMatrix(& mat_transit);
}
