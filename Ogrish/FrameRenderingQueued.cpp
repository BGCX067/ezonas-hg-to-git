#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	// gor_rect -> ();
	gor_caption -> text(Ogre::StringConverter::toString(window -> getLastFPS()));
	return fpersoncam -> update(evt.timeSinceLastFrame);
}

