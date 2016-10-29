#pragma once
#ifndef __TANK_STATE_MACHINE_HPP__
#define __TANK_STATE_MACHINE_HPP__

#include "ITankState.hpp"

class TankStateMachine
{
public:
    TankStateMachine() :
        mState(nullptr)
    {
    }

private:
    ITankState* mState;
};

#endif // __TANK_STATE_MACHINE_HPP__
