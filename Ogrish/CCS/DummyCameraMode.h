#ifndef _DummyCameraModes_H_
#define _DummyCameraModes_H_
#include "stdafx.h"
// This is an example of how a custom camera mode can be implemented

class DummyCameraMode : public CCS::CameraControlSystem::CameraMode
{
public:
	DummyCameraMode(CCS::CameraControlSystem* cam, Ogre::Real speed = 1)
		: CameraMode(cam)
	{ 
		mSpeed = speed;
		mDirectionWhenStopped = 1;
	}

	~DummyCameraMode(){};

	virtual bool init()
    {
        mCameraCS->setFixedYawAxis(false);
        mCameraCS->setAutoTrackingTarget(false);

		mCurrentDirection = mDirectionWhenStopped;

        instantUpdate();

        return true;
    }

	virtual void stop()
	{
		mDirectionWhenStopped = mCurrentDirection;
	}


    virtual void update(const Ogre::Real &timeSinceLastFrame)
	{
		Ogre::Vector3 currentPosition = mCameraCS->getCameraSceneNode()->getPosition();
		
		if(currentPosition.z > 1000) mCurrentDirection = -1;
		else if(currentPosition.z < -1000) mCurrentDirection = 1;

		mCameraPosition += Ogre::Vector3(0,0, mSpeed * mCurrentDirection * timeSinceLastFrame);
		//mCameraOrientation = Ogre::Quaternion::IDENTITY;
	}

    virtual void instantUpdate()
    {
		mCameraPosition = Ogre::Vector3::ZERO;
		mCameraOrientation = Ogre::Quaternion::IDENTITY;
    }


protected:
	Ogre::Real mSpeed;
	Ogre::Real mCurrentDirection;
	Ogre::Real mDirectionWhenStopped;
};

#endif
