/*
 * State when the tank attacks enemy tanks
 *
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 *
 * The tank will scan for any enemy in range,
 * if there are, it will attack the target, if not
 * it will go back to wander state.
 */

#pragma once
#ifndef __ATTACK_STATE_HPP__
#define __ATTACK_STATE_HPP__

#include "TankState.hpp"

class AttackState : public TankState
{
public:
    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override;

    Type GetType() const override
    {
        return Type::ATTACK;
    }
};

#endif // __ATTACK_STATE_HPP__