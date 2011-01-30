#include "stdafx.h"

CursorChecker :: CursorChecker(Mouse * _mouse, Camera * _camera):
	camera(_camera),
	mouse(_mouse),
	cursor_ray (camera -> getPosition(), camera -> getDirection())
{}


void CursorChecker :: UpdateRay()
{
}



