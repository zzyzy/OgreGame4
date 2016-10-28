/*
 * Projectile class.
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Basic projectile class.
 */

#pragma once
#ifndef __PROJECTILE_HPP__
#define __PROJECTILE_HPP__

#include "GameObject.hpp"
#include "IPhysicsObject.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsEngine.h"

class Projectile : public GameObject, public IPhysicsObject
{
public:
    explicit Projectile(PhysicsEngine* physics,
                        btRigidBody* body) :
        mPhysicsComponent(new PhysicsObject(physics, body, this))
    {
        AddComponent(mPhysicsComponent);
    }

    void SetLinearVelocity(const btVector3& velocity) override
    {
        mPhysicsComponent->GetRBody()->setLinearVelocity(velocity);
    }

    void SetGravity(const btVector3& acceleration) override
    {
        mPhysicsComponent->GetRBody()->setGravity(acceleration);
    }

protected:
    PhysicsObject* mPhysicsComponent;
};

#endif // __PROJECTILE_HPP__
