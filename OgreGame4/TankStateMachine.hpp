/*
 * Tank state machine
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Handles state changes in the tank
 * Adapted from:
 * http://gameprogrammingpatterns.com/state.html
 */

#pragma once
#ifndef __TANK_STATE_MACHINE_HPP__
#define __TANK_STATE_MACHINE_HPP__

#include "TankState.hpp"

class Tank;

class TankStateMachine
{
public:
    TankStateMachine() :
        mState(nullptr),
        mTank(nullptr)
    {
    }

    ~TankStateMachine()
    {
        if (mState)
            delete mState;
    }

    explicit TankStateMachine(TankState* state, Tank* tank) :
        mState(state),
        mTank(tank)
    {
        assert(state != nullptr);
        assert(tank != nullptr);
    }

    TankStateMachine(const TankStateMachine& other) :
        mState(other.mState),
        mTank(other.mTank)
    {
    }

    TankStateMachine(TankStateMachine&& other) :
        mState(other.mState),
        mTank(other.mTank)
    {
        other.mState = nullptr;
    }

    TankStateMachine& operator=(const TankStateMachine& other)
    {
        auto tmp(other);
        *this = std::move(tmp);
        return *this;
    }

    TankStateMachine& operator=(TankStateMachine&& other)
    {
        if (mState)
            delete mState;
        mState = other.mState;
        other.mState = nullptr;
        mTank = other.mTank;
        return *this;
    }

    void SetState(TankState* state)
    {
        assert(state != nullptr);
        if (mState)
            delete mState;
        mState = state;
    }

    TankState* GetState() const
    {
        return mState;
    }

    Tank* GetTank() const
    {
        return mTank;
    }

    void Update(const float& deltaTime)
    {
        assert(mState != nullptr);
        TankState* state = mState->Update(*this, deltaTime);
        if (state != nullptr)
        {
            switch (state->GetType())
            {
            case TankState::Type::POWERUP:
                std::cout << "Powerup" << std::endl;
                break;
            case TankState::Type::DESTROYED:
                std::cout << "Destroyed" << std::endl;
                break;
            case TankState::Type::ATTACK:
                std::cout << "Attack" << std::endl;
                break;
            case TankState::Type::SPAWN:
                std::cout << "Spawn" << std::endl;
                break;
            case TankState::Type::TROPHY:
                std::cout << "Trophy" << std::endl;
                break;
            case TankState::Type::WANDER:
                std::cout << "Wander" << std::endl;
                break;
            default:
                break;
            }

            delete mState;
            mState = state;
        }
    }

private:
    TankState* mState;
    Tank* mTank;
};

#endif // __TANK_STATE_MACHINE_HPP__
