#include "stdafx.h"

// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
	gor_caption[1] -> text(Ogre::StringConverter::toString(window -> getLastFPS()));
	frame_time = evt.timeSinceLastFrame;
	return fpersoncam -> update();//evt.timeSinceLastFrame);
}

