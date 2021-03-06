#pragma once
#ifndef __TROPHY_HPP__
#define __TROPHY_HPP__

#include "TankCollider.hpp"

class Trophy : public Ogre::SceneNode, public IPoolObject
{
public:
    Trophy(Ogre::SceneManager* creator, PhysicsEngine* physics, float* lpScore, float* chScore) :
        SceneNode(creator),
        mCollider(nullptr),
        mPhysics(physics),
        mIsDisposable(false),
        mIsDisposed(false),
        mLPTeamScore(lpScore),
        mCHTeamScore(chScore)
    {
    }

    void SetCollider(btPairCachingGhostObject* collider) { mCollider = collider; }
    btPairCachingGhostObject* GetCollider() const { return mCollider; }

    static const int mScoreValue = 10;

    // Allow the pool manager to update the pool object
    void Update(const float& deltaTime) override
    {
        auto co = mPhysics->GetCollidedObject(mCollider);

        if (co)
        {
            auto tankCol = dynamic_cast<TankCollider*>(co);

            if (tankCol)
            {
                tankCol->GetTank()->AddScore(mScoreValue);

                if (tankCol->GetTank()->GetType() == Tank::Type::LEOPARD)
                {
                    *mLPTeamScore += mScoreValue;
                } else
                {
                    *mCHTeamScore += mScoreValue;
                }

                mIsDisposable = true;
            }
        }
    }

    // Is this object disposable?
    bool IsDisposable() const override
    {
        return mIsDisposable;
    }

    // Is this object disposed?
    bool IsDisposed() const override
    {
        return mIsDisposed;
    }

    // Dispose this object, basically cleaning up
    // and release any unused memory/dangling pointers
    void Dispose() override
    {
        mPhysics->DestroyGhostObject(mCollider);
        mIsDisposed = true;
    }

private:
    btPairCachingGhostObject* mCollider;
    PhysicsEngine* mPhysics;
    bool mIsDisposable;
    bool mIsDisposed;
    float* mLPTeamScore;
    float* mCHTeamScore;
};

#endif // __TROPHY_HPP__
