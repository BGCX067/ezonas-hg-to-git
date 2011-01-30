#include "stdafx.h"

class CursorChecker
{
public:
	CursorChecker(Mouse * m, Camera * cam);
	~ CursorChecker ();
	void UpdateRay();
protected:
	Camera * cam;
	Mouse * mouse;

};