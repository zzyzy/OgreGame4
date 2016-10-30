/*
 * Seek powerup state
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * In this state the tank will look for powerups,
 * and move to acquire them via path finding.
 */

#pragma once
#ifndef __FIND_POWERUP_STATE_HPP__
#define __FIND_POWERUP_STATE_HPP__

#include "TankState.hpp"

class FindPowerupState : public TankState
{
public:
    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override;

    Type GetType() const override
    {
        return Type::TROPHY;
    }
}

#endif // __FIND_POWERUP_STATE_HPP__