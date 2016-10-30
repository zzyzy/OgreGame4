/*
 * Wander state
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * State when the tank wanders around in the battleground.
 * Contains decision making on whether to seek trophies,
 * powerups or attack enemies.
 */

#pragma once
#ifndef __WANDER_STATE_HPP__
#define __WANDER_STATE_HPP__

#include "TankState.hpp"

class WanderState : public TankState
{
public:
    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override
    {
        return nullptr;
    }

    Type GetType() const override
    {
        return Type::WANDER;
    }
};

#endif // __WANDER_STATE_HPP__
