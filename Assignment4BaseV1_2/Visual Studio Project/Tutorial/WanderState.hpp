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
#include <random>

class WanderState : public TankState
{
public:
    WanderState() :
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
            mMoveLocation = Ogre::Vector3::ZERO;
        }

        auto object = tank->GetNearestObject();
        auto enemyTank = dynamic_cast<Tank*>(object);
        if (enemyTank && enemyTank->GetType() != tank->GetType())
        {
            tank->FireAt(enemyTank->getPosition());
        }

        return nullptr;
    }

    Type GetType() const override
    {
        return Type::WANDER;
    }

private:
    Ogre::Vector3 mMoveLocation;
    std::mt19937 mRNG;
};

#endif // __WANDER_STATE_HPP__
