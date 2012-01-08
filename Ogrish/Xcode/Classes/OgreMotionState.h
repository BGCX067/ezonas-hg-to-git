#ifndef __APPLE__
#include "stdafx.h"
#endif
#ifdef PHYSICS

class OgreMotionState : public btMotionState
{
public:
    OgreMotionState(const btTransform &initialpos, Ogre :: SceneNode *node);
    virtual ~ OgreMotionState() {}
    void setNode(Ogre :: SceneNode *node);
    virtual void getWorldTransform(btTransform &worldTrans) const;
    virtual void setWorldTransform(const btTransform &worldTrans);

protected:
    Ogre :: SceneNode *mVisibleobj;
    btTransform mPos1;
};
#endif
