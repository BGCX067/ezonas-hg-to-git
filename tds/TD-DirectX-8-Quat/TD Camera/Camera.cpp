//////////////////////////////////////////////////////////////////////////////////////////////////
// 
// File: camera.cpp
// 
// Author: Frank Luna (C) All Rights Reserved
//
// System: AMD Athlon 1800+ XP, 512 DDR, Geforce 3, Windows XP, MSVC++ 7.0 
//
// Desc: Defines a camera's position and orientation.
//         
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "camera.h"

Camera::Camera()
{
	_pos   = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	_right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	_up    = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	_look  = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
}
Camera::Camera(Camera& _Cam)
{
	_pos   = _Cam._pos;
	_right = _Cam._right;
	_up    = _Cam._up;
	_look  = _Cam._look;
}
Camera::~Camera(){}
void Camera::getPosition(D3DXVECTOR3* pos){*pos = _pos;}
void Camera::setPosition(D3DXVECTOR3* pos){_pos = *pos;}
void Camera::getRight(D3DXVECTOR3* right){*right = _right;}
void Camera::getUp(D3DXVECTOR3* up){*up = _up;}
void Camera::getLook(D3DXVECTOR3* look){*look = _look;}
void Camera::walk(float units){}
void Camera::strafe(float units){}
void Camera::fly(float units){}
void Camera::pitch(float angle)
{
	D3DXMATRIX T;
	D3DXMatrixRotationAxis(&T, &_right,	angle);

	// rotate _up and _look around _right vector
	D3DXVec3TransformCoord(&_up,&_up, &T);
	D3DXVec3TransformCoord(&_look,&_look, &T);
}
void Camera::yaw(float angle)
{
}
void Camera::roll(float angle)
{
}
void Camera::getViewMatrix(D3DXMATRIX* V)
{
	// Keep camera's axes orthogonal to each other
	D3DXVec3Normalize(&_look, &_look);

	D3DXVec3Cross(&_up, &_look, &_right);
	D3DXVec3Normalize(&_up, &_up);

	D3DXVec3Cross(&_right, &_up, &_look);
	D3DXVec3Normalize(&_right, &_right);

	// Build the view matrix:
	float x = -D3DXVec3Dot(&_right, &_pos);
	float y = -D3DXVec3Dot(&_up, &_pos);
	float z = -D3DXVec3Dot(&_look, &_pos);

	(*V)(0,0) = _right.x; (*V)(0, 1) = _up.x; (*V)(0, 2) = _look.x; (*V)(0, 3) = 0.0f;
	(*V)(1,0) = _right.y; (*V)(1, 1) = _up.y; (*V)(1, 2) = _look.y; (*V)(1, 3) = 0.0f;
	(*V)(2,0) = _right.z; (*V)(2, 1) = _up.z; (*V)(2, 2) = _look.z; (*V)(2, 3) = 0.0f;
	(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
}
void Camera::update(float timeDelta)
{
	// duh
}


void Camera :: setViewMatrix(D3DXMATRIX* V)
{

	_right.x = (*V)(0,0); _up.x = (*V)(0, 1); _look.x = (*V)(0, 2);
	_right.y = (*V)(1,0); _up.y = (*V)(1, 1); _look.y = (*V)(1, 2);
	_right.z = (*V)(2,0); _up.z = (*V)(2, 1); _look.z = (*V)(2, 2);
	//(*V)(3,0) = x;        (*V)(3, 1) = y;     (*V)(3, 2) = z;       (*V)(3, 3) = 1.0f;
	D3DXVec3Normalize(&_look, &_look);
	D3DXVec3Normalize(&_up, &_up);
	D3DXVec3Normalize(&_right, &_right);
}