#pragma once
#ifndef __OBJECT_FACTORY_HPP__
#define __OBJECT_FACTORY_HPP__

#include "PhysicsEngine.h"
#include "Trophy.hpp"
#include "PowerUp.h"

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

    Trophy* MakeTrophy(const Ogre::Vector3& position, float* lpScore, float* chScore) const;
    PowerUp* MakePowerUp(const Ogre::Vector3& position, PowerUp::Type type) const;

private:
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
};

#endif // __OBJECT_FACTORY_HPP__