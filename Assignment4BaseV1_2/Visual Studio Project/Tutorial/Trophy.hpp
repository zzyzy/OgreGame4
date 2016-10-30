#pragma once
#ifndef __TROPHY_HPP__
#define __TROPHY_HPP__

class Trophy : public Ogre::SceneNode
{
public:
    Trophy(Ogre::SceneManager* creator) :
        SceneNode(creator),
        mRBody(nullptr)
    {
    }

    void SetRBody(btRigidBody* rbody) { mRBody = rbody; }
    btRigidBody* GetRBody() const { return mRBody; }

    static const int mScoreValue = 10;

private:
    btRigidBody* mRBody;
};

#endif // __TROPHY_HPP__
