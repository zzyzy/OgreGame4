/*
 * State when the tank spawns or respawns
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Handles the state when the tank spawns or respawns.
 * Moves to the battleground via path finding.
 * Once it reaches the battleground, it'll switch to
 * the wander state.
 */

#pragma once
#ifndef __SPAWN_STATE_HPP__
#define __SPAWN_STATE_HPP__

#include "TankState.hpp"
#include <random>

class SpawnState : public TankState
{
public:
    SpawnState() :
        mMoveLocation(Ogre::Vector3::ZERO),
        mRNG(std::random_device()())
    {
    }

    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override;

    Type GetType() const override
    {
        return Type::SPAWN;
    }

private:
    Ogre::Vector3 mMoveLocation;
    std::mt19937 mRNG;
};

#endif // __SPAWN_STATE_HPP__
