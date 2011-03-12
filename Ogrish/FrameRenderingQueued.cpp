#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	return fpersoncam -> update(evt.timeSinceLastFrame);
}

