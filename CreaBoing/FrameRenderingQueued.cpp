#include "stdafx.h"
// ############################# frameStarted #############################
bool Application :: frameRenderingQueued(const FrameEvent & evt)
{
        gor_caption[1] -> text
        (
                TO_STR((int)(window -> getLastFPS())) + " fps "
                + TO_STR((int)window -> getTriangleCount()) + " tri; "
                //+ TO_STR((int)window -> getBatchCount()) + " bat; "
                + "pos " + TO_STR((int)position.y) + " "
                + "vel: " + TO_STR((int)velocity.y)
        );
        frame_time = evt.timeSinceLastFrame;

		position += velocity * frame_time;
        velocity += gravity * frame_time;

        if(position.y < 0.0f)
        {
			velocity.y = 20;
			position.y = 0;
			impact = position;
        }
        n_ball -> setPosition(position);

        return cam_ctrlr -> update();
}
