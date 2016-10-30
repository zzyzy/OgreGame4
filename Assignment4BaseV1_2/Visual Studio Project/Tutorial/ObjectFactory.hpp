#pragma once
#ifndef __OBJECT_FACTORY_HPP__
#define __OBJECT_FACTORY_HPP__

#include "PhysicsEngine.h"
#include "Trophy.hpp"

class ObjectFactory
{
public:
    explicit ObjectFactory(Ogre::SceneManager* world,
        PhysicsEngine* physics) :
        mWorld(world),
        mPhysics(physics)
    {
        assert(world != nullptr);
        assert(physics != nullptr);
    }

    Trophy* MakeTrophy(const Ogre::Vector3& position) const;

private:
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
};

#endif // __OBJECT_FACTORY_HPP__