#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text(Ogre::StringConverter::toString(window -> getLastFPS()));
	return fpersoncam -> update(evt.timeSinceLastFrame);
}

