#pragma once
#ifndef __POWERUP_EFFECT_HPP__
#define __POWERUP_EFFECT_HPP__

#include "IPoolObject.hpp"

class PowerUpEffect : public IPoolObject
{
public:
    PowerUpEffect(const float& original, const float& powerUpVal, const float& duration, float* ptr) :
        mOriginalValue(original),
        mPowerUpValue(powerUpVal),
        mPowerUpDuration(duration),
        mTimer(0.0f),
        mPowerUpPtr(ptr),
        mIsDisposable(false),
        mIsDisposed(false)
    {
        assert(ptr != nullptr);
    }

    void Update(const float& deltaTime) override
    {
        if (mTimer < mPowerUpDuration)
        {
            mTimer += deltaTime;
            *mPowerUpPtr = mPowerUpValue;
        }
        else
        {
            *mPowerUpPtr = mOriginalValue;
            mIsDisposable = true;
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
        mIsDisposed = true;
    }

private:
    float mOriginalValue;
    float mPowerUpValue;
    float mPowerUpDuration;
    float mTimer;
    float* mPowerUpPtr;
    bool mIsDisposable;
    bool mIsDisposed;
};

#endif // __POWERUP_EFFECT_HPP__