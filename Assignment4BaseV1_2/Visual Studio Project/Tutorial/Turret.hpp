/*
 * Tank turret
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Tank turret that launches tank shells towards a
 * target location. Able to define the shell speed,
 * shell mass, delay between shots, shell blast force
 * as well as the shell blast radius. For realism,
 * the tank barrel pitches smoothly towards the
 * calculated projectile velocity direction.
 */

#pragma once
#ifndef __TURRET_HPP__
#define __TURRET_HPP__

#include "PhysicsEngine.h"
#include "PoolManager.hpp"

class Turret
{
public:
    Turret();

    Turret(Ogre::SceneNode* turret,
           Ogre::SceneNode* barrel,
           Ogre::SceneNode* nozzle,
           Ogre::SceneManager* world,
           PhysicsEngine* physics,
           const size_t& maxPoolSize,
           const float& delayBetweenShots = 1.0f,
           const float& shellSpeed = 250.0f,
           const float& shellMass = 2.0f,
           const float& blastForce = 0.5f,
           const float& blastRadius = 5.0f);

    Turret(const Turret& turret);

    Turret(Turret&& turret);

    Turret& operator=(const Turret& turret);

    Turret& operator=(Turret&& turret);

    void Update(const float& deltaTime);

    bool IsReady() const;

    void GetLookAtRotations(const Ogre::Vector3& target,
                            Ogre::Quaternion* turretRotation,
                            Ogre::Quaternion* barrelRotation) const;

    void SmoothRotate(const Ogre::Quaternion& turretRotation,
                      const Ogre::Quaternion& barrelRotation,
                      const float& deltaTime) const;

    bool FireAt(const Ogre::Vector3& target);

    // Getters
    float GetDelayBetweenShots() const { return mDelayBetweenShots; }
    float GetShellSpeed() const { return mShellSpeed; }
    float GetShellMass() const { return mShellMass; }
    float GetBlastForce() const { return mBlastForce; }
    float GetBlastRadius() const { return mBlastRadius; }

    // Setters
    void SetDelayBetweenShots(const float& delay) { mDelayBetweenShots = delay; }
    void SetShellSpeed(const float& speed) { mShellSpeed = speed; }
    void SetShellMass(const float& mass) { mShellMass = mass; }
    void SetBlastForce(const float& force) { mBlastForce = force; }
    void SetBlastRadius(const float& radius) { mBlastRadius = radius; }

private:
    Ogre::SceneNode* mTurret;
    Ogre::SceneNode* mBarrel;
    Ogre::SceneNode* mNozzle;
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
    PoolManager mPool;
    float mDelayBetweenShots;
    float mElapsedDelay;
    float mShellSpeed;
    float mShellMass;
    float mBlastForce;
    float mBlastRadius;
    Ogre::Vector3 mProjectileVelocity;
    float mProjectileGravity;
};

#endif // __TURRET_HPP__
