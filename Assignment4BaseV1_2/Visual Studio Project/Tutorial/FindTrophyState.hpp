/*
 * Seek trophy state
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * This is similar to FindPowerupState, instead of
 * powerups, it will look for trophies and move
 * to acquire it using path finding.
 */

#pragma once
#ifndef __FIND_TROPHY_STATE_HPP__
#define __FIND_TROPHY_STATE_HPP__

#include "TankState.hpp"

class FindTrophyState : public TankState
{
public:
    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override;

    Type GetType() const override
    {
        return Type::TROPHY;
    }
};

#endif // __FIND_TROPHY_STATE_HPP__