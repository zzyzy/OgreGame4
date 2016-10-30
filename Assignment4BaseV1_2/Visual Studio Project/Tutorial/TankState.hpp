/*
* Base class for tank states
*
* Copyright (C) 2016 Zhen Zhi Lee
* Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
*
* All possible states for the tank must inherit
* from this class for the state machine pattern
* to work.
*/

#pragma once
#ifndef __TANK_STATE_HPP__
#define __TANK_STATE_HPP__

class TankStateMachine;

class TankState
{
public:
    enum class Type
    {
        SPAWN,
        BATTLEGROUND,
        WANDER,
        POWERUP,
        TROPHY,
        ATTACK,
        DESTROYED
    };

    virtual ~TankState()
    {
    }

    virtual TankState* Update(TankStateMachine& tankState, const float& deltaTime) = 0;

    virtual Type GetType() const = 0;

    virtual bool operator==(const Type& state)
    {
        return GetType() == state;
    }

    friend bool operator==(const TankState* const& lhs, const Type& rhs)
    {
        return lhs->GetType() == rhs;
    }
};

#endif // __TANK_STATE_HPP__
