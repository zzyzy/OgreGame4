/*
 * Tank shell
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * A tank shell that launches from the tank barrel.
 * Explodes on impact and dealing damage to nearby
 * objects based on the distance between the object
 * and the impact point.
 */

#pragma once
#ifndef __SHELL_HPP__
#define __SHELL_HPP__

#include "Projectile.hpp"
#include "IPoolObject.hpp"
#include "CollisionMasks.hpp"
#include "IDamageableObject.hpp"
#include "Tank.h"
#include "TankCollider.hpp"

class Shell : public Projectile, public IPoolObject
{
public:
    Shell(btRigidBody* rbody,
          Ogre::SceneManager* world,
          PhysicsEngine* physics,
          const float& blastForce,
          const float& blastRadius,
          const float& blastDuration = 2.0f) :
        Projectile(rbody, physics),
        mWorld(world),
        mBlastForce(blastForce),
        mBlastRadius(blastRadius),
        mBlastDuration(blastDuration),
        mBlastTimer(0.0f),
        mDisposed(false),
        mBlastCollider(nullptr),
        mParticleSystem(nullptr),
        mParticleNode(nullptr)
    {
        assert(rbody != nullptr);
        assert(world != nullptr);
        assert(physics != nullptr);
    }

    void Update(const float& deltaTime) override
    {
        if (mBlastTimer >= mBlastDuration) return;

        if (mRBody)
        {
            auto collidedObjects = mPhysics->GetAllCollidedObjects(mRBody);

            if (mRBody->getCenterOfMassPosition().y() < 1.0f || !collidedObjects.empty())
            {
                assert(mBlastCollider == nullptr);

                btTransform startTrans = mRBody->getCenterOfMassTransform();
                btCollisionShape* shape = new btSphereShape(mBlastRadius);

                // Visualize blast radius
                /*
                auto mDummyEntity = mWorld->createEntity("sphere.mesh");
                auto mDummyNode = mWorld->getRootSceneNode()->createChildSceneNode();
                mDummyNode->attachObject(mDummyEntity);
                mDummyNode->setPosition(Convert(startTrans.getOrigin()));
                mDummyNode->scale(0.01f * mBlastRadius, 0.01f * mBlastRadius, 0.01f * mBlastRadius);
                */

                mBlastCollider = mPhysics->CreateGhostObject(startTrans, shape,
                                                             static_cast<short>(CollisionTypes::EXPLOSION),
                                                             CollisionTypes::TANK |
                                                             CollisionTypes::OBSTACLES);
                mBlastCollider->setCollisionFlags(mBlastCollider->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);

                // create a particle system named explosions using the explosionTemplate
                std::stringstream stream;
                stream << this << "_Explosion";
                auto name = stream.str();
                mParticleSystem = mWorld->createParticleSystem(name, "explosionTemplate");
                // attach the particle system to a scene node
                mParticleNode = mWorld->getRootSceneNode()->createChildSceneNode();
                mParticleNode->attachObject(mParticleSystem);
                mParticleNode->setPosition(convert(mRBody->getCenterOfMassPosition()));
                mParticleNode->translate(0, 4, 0);
                // fast forward to the point where the particle has been emitted
                mParticleSystem->fastForward(4.6f);

                // Remove the projectile
                auto node = static_cast<MyMotionState*>(mRBody->getMotionState())->getNode();
                auto entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
                node->detachAllObjects();
                mWorld->destroyEntity(entity);
                mWorld->destroySceneNode(node);
                mPhysics->destroyRigidBody(mRBody);
                mRBody = nullptr;
            }
        }
        else
        {
            auto collidedObjects = mPhysics->GetAllCollidedObjects(mBlastCollider);

            for (auto it = collidedObjects.begin(); it != collidedObjects.end(); ++it)
            {
                auto rbody = dynamic_cast<btRigidBody*>(*it);
                auto tankCol = dynamic_cast<TankCollider*>(*it);

                if (rbody)
                {
                    auto rayFromWorld = mBlastCollider->getWorldTransform().getOrigin();
                    auto rayToWorld = rbody->getCenterOfMassPosition();
                    auto impulse = rayToWorld - rayFromWorld;

                    impulse.normalize();
                    impulse *= mBlastForce;

                    mPhysics->ShootRay(rayFromWorld, rayToWorld, impulse);
                }

                if (tankCol)
                {
                    auto tank = tankCol->GetTank();

                    if (tank)
                    {
                        auto rayFromWorld = mBlastCollider->getWorldTransform().getOrigin();
                        auto rayToWorld = tankCol->getWorldTransform().getOrigin();
                        auto damage = (rayToWorld - rayFromWorld).length() * 0.1f;
                        tank->ApplyDamage(damage);
                    }
                }
            }

            mBlastTimer += deltaTime;
        }
    }

    bool IsDisposable() const override
    {
        return mBlastTimer >= mBlastDuration;
    }

    bool IsDisposed() const override
    {
        return mDisposed;
    }

    void Dispose() override
    {
        mPhysics->DestroyGhostObject(mBlastCollider);
        mParticleNode->detachAllObjects();
        mWorld->destroyParticleSystem(mParticleSystem);
        mWorld->destroySceneNode(mParticleNode);
        mWorld = nullptr;
        mBlastCollider = nullptr;
        mParticleSystem = nullptr;
        mParticleNode = nullptr;
        mDisposed = true;
    }

private:
    Ogre::SceneManager* mWorld;
    float mBlastForce;
    float mBlastRadius;
    float mBlastDuration;
    float mBlastTimer;
    bool mDisposed;
    btPairCachingGhostObject* mBlastCollider;
    Ogre::ParticleSystem* mParticleSystem;
    Ogre::SceneNode* mParticleNode;
};

#endif // __SHELL_HPP__
