/*
 * Tank factory
 *
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Factory that spawns tanks
 */

#pragma once
#ifndef __TANK_FACTORY_HPP__
#define __TANK_FACTORY_HPP__

#include "Tank.h"

class TankFactory
{
public:
    explicit TankFactory(Ogre::SceneManager* world,
                         PhysicsEngine* physics) :
        mWorld(world),
        mPhysics(physics)
    {
        assert(world != nullptr);
        assert(physics != nullptr);
    }

    Tank* MakeChallengerTank(const Ogre::Vector3& position,
                             Graph* graph,
                             PathFinding* pathFinder) const;

    Tank* MakeLeopardTank(const Ogre::Vector3& position,
                          Graph* graph,
                          PathFinding* pathFinder) const;

private:
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
};

#endif // __TANK_FACTORY_HPP__
