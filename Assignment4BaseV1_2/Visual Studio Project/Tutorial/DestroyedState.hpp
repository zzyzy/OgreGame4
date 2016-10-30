#pragma once
#ifndef __DESTROYED_STATE_HPP__
#define __DESTROYED_STATE_HPP__

#include "TankState.hpp"

class DestroyedState : public TankState
{
public:
    explicit DestroyedState(const float& respawnTime) :
        mRespawnTime(respawnTime),
        mTimer(0.0f)
    {
    }

    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override;

    Type GetType() const override
    {
        return Type::DESTROYED;
    }

private:
    float mRespawnTime;
    float mTimer;
};

#endif // __DESTROYED_STATE_HPP__
