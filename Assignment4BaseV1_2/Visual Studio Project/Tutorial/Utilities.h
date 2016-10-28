/*
 * Utilities from tutorial
 * LookRotation from Unity3D
 */

#pragma once
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

inline Ogre::Vector3 convert(const btVector3& vec3)
{
    return Ogre::Vector3(vec3.x(), vec3.y(), vec3.z());
}

inline btVector3 convert(const Ogre::Vector3& vec3)
{
    return btVector3(vec3.x, vec3.y, vec3.z);
}

inline btQuaternion convert(const Ogre::Quaternion& Q)
{
    return btQuaternion(Q.x, Q.y, Q.z, Q.w);
}

inline Ogre::Quaternion convert(const btQuaternion& Q)
{
    return Ogre::Quaternion(Q.w(), Q.x(), Q.y(), Q.z());
}

Ogre::Quaternion LookRotation(Ogre::Vector3 forward, Ogre::Vector3 up);

class MyMotionState : public btMotionState
{
public:
    MyMotionState(const btTransform& initialpos, Ogre::SceneNode* node)
    {
        mVisibleobj = node;
        mPos1 = initialpos;
    }

    virtual ~MyMotionState()
    {
    }

    void setNode(Ogre::SceneNode* node)
    {
        mVisibleobj = node;
    }

    void getWorldTransform(btTransform& worldTrans) const override
    {
        worldTrans = mPos1;
    }

    void setWorldTransform(const btTransform& worldTrans) override
    {
        if (NULL == mVisibleobj)
            return; // silently return before we set a node
        btQuaternion rot = worldTrans.getRotation();
        mVisibleobj->setOrientation(rot.w(), rot.x(), rot.y(), rot.z());
        btVector3 pos = worldTrans.getOrigin();
        mVisibleobj->setPosition(pos.x(), pos.y(), pos.z());
    }

    Ogre::SceneNode* getNode() const
    {
        return mVisibleobj;
    }

protected:
    Ogre::SceneNode* mVisibleobj;
    btTransform mPos1;
};

#endif // __UTILITIES_H__
