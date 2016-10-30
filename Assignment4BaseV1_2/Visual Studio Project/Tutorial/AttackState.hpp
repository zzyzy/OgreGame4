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