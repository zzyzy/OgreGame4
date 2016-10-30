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
#include "TankStateMachine.hpp"
#include "Tank.h"
#include <random>
#include "WanderState.hpp"

class SpawnState : public TankState
{
public:
    SpawnState() :
        mMoveLocation(Ogre::Vector3::ZERO),
        mRNG(std::random_device()())
    {
    }

    TankState* Update(TankStateMachine& tankState, const float& deltaTime) override
    {
        Tank* tank = tankState.GetTank();

        if (mMoveLocation == Ogre::Vector3::ZERO)
        {
            std::uniform_real_distribution<float> xDis(-60, 60);
            std::uniform_real_distribution<float> zDis(-70, 70);
            mMoveLocation = Ogre::Vector3(xDis(mRNG), 0, zDis(mRNG));

            // Move to location
            tank->MoveTo(mMoveLocation);
        }
        
        if (tank->getPosition().positionEquals(mMoveLocation, 10.0f))
        {
            return new WanderState();
        }

        return nullptr;
    }

    Type GetType() const override
    {
        return Type::SPAWN;
    }

private:
    Ogre::Vector3 mMoveLocation;
    std::mt19937 mRNG;
};

#endif // __SPAWN_STATE_HPP__
