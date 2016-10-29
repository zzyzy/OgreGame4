/*
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 */

#include "Turret.hpp"
#include "ProjectileMath.hpp"
#include "OgreEuler.hpp"
#include "Shell.hpp"

Turret::Turret() :
    mTurret(nullptr),
    mBarrel(nullptr),
    mNozzle(nullptr),
    mWorld(nullptr),
    mPhysics(nullptr),
    mPool(1), 
    mTargetType(),
    mDelayBetweenShots(0.0f),
    mElapsedDelay(0.0f),
    mShellSpeed(0.0f),
    mShellMass(0.0f),
    mBlastForce(0.0f),
    mBlastRadius(0.0f),
    mProjectileVelocity(Ogre::Vector3::ZERO),
    mProjectileGravity(0.0f)
{
}

Turret::Turret(Ogre::SceneNode* turret,
               Ogre::SceneNode* barrel,
               Ogre::SceneNode* nozzle,
               Ogre::SceneManager* world,
               PhysicsEngine* physics,
               const size_t& maxPoolSize,
               const CollisionTypes& targetType,
               const float& delayBetweenShots,
               const float& shellSpeed,
               const float& shellMass,
               const float& blastForce,
               const float& blastRadius) :
    mTurret(turret),
    mBarrel(barrel),
    mNozzle(nozzle),
    mWorld(world),
    mPhysics(physics),
    mPool(maxPoolSize), 
    mTargetType(targetType),
    mDelayBetweenShots(delayBetweenShots),
    mElapsedDelay(delayBetweenShots),
    mShellSpeed(shellSpeed),
    mShellMass(shellMass),
    mBlastForce(blastForce),
    mBlastRadius(blastRadius),
    mProjectileVelocity(Ogre::Vector3::ZERO),
    mProjectileGravity(0.0f)
{
    assert(turret != nullptr);
    assert(barrel != nullptr);
    assert(nozzle != nullptr);
    assert(world != nullptr);
    assert(physics != nullptr);
    assert(maxPoolSize > 0);
}

Turret::Turret(const Turret& turret) :
    mTurret(turret.mTurret),
    mBarrel(turret.mBarrel),
    mNozzle(turret.mNozzle),
    mWorld(turret.mWorld),
    mPhysics(turret.mPhysics),
    mPool(turret.mPool),
    mTargetType(turret.mTargetType),
    mDelayBetweenShots(turret.mDelayBetweenShots),
    mElapsedDelay(turret.mElapsedDelay),
    mShellSpeed(turret.mShellSpeed),
    mShellMass(turret.mShellMass),
    mBlastForce(turret.mBlastForce),
    mBlastRadius(turret.mBlastRadius),
    mProjectileVelocity(turret.mProjectileVelocity),
    mProjectileGravity(turret.mProjectileGravity)
{
}

Turret::Turret(Turret&& turret) :
    mTurret(turret.mTurret),
    mBarrel(turret.mBarrel),
    mNozzle(turret.mNozzle),
    mWorld(turret.mWorld),
    mPhysics(turret.mPhysics),
    mPool(std::move(turret.mPool)),
    mTargetType(turret.mTargetType),
    mDelayBetweenShots(turret.mDelayBetweenShots),
    mElapsedDelay(turret.mElapsedDelay),
    mShellSpeed(turret.mShellSpeed),
    mShellMass(turret.mShellMass),
    mBlastForce(turret.mBlastForce),
    mBlastRadius(turret.mBlastRadius),
    mProjectileVelocity(turret.mProjectileVelocity),
    mProjectileGravity(turret.mProjectileGravity)
{
}

Turret& Turret::operator=(const Turret& turret)
{
    Turret tmp(turret);
    *this = std::move(tmp);
    return *this;
}

Turret& Turret::operator=(Turret&& turret)
{
    mTurret = turret.mTurret;
    mBarrel = turret.mBarrel;
    mNozzle = turret.mNozzle;
    mWorld = turret.mWorld;
    mPhysics = turret.mPhysics;
    mPool = std::move(turret.mPool);
    mTargetType = turret.mTargetType;
    mDelayBetweenShots = turret.mDelayBetweenShots;
    mElapsedDelay = turret.mElapsedDelay;
    mShellSpeed = turret.mShellSpeed;
    mShellMass = turret.mShellMass;
    mBlastForce = turret.mBlastForce;
    mBlastRadius = turret.mBlastRadius;
    mProjectileVelocity = turret.mProjectileVelocity;
    mProjectileGravity = turret.mProjectileGravity;
    return *this;
}

void Turret::Update(const float& deltaTime)
{
    if (mElapsedDelay < mDelayBetweenShots)
    {
        mElapsedDelay += deltaTime;
    }

    mPool.Update(deltaTime);

    // If there's no calculated projectile velocity, skip the rest of the operation
    if (mProjectileVelocity == Ogre::Vector3::ZERO) return;

    // Turn the turret and adjust the barrel
    Ogre::Quaternion turretRotation, barrelRotation;
    GetLookAtRotations(mProjectileVelocity, &turretRotation, &barrelRotation);
    SmoothRotate(turretRotation, barrelRotation, deltaTime);

    // If barrel is in position, fire the projectile
    if (mTurret->getOrientation().equals(turretRotation, Ogre::Degree(0.01f)) &&
        mBarrel->getOrientation().equals(barrelRotation, Ogre::Degree(0.01f)) &&
        mPool.CurrentSize() < mPool.MaxSize() &&
        IsReady())
    {
        auto entity = mWorld->createEntity("sphere.mesh");
        auto node = mWorld->getRootSceneNode()->createChildSceneNode();
        auto shape = new btBoxShape(btVector3(1, 1, 1));
        auto position = mNozzle->_getDerivedPosition();
        btTransform transform;

        entity->setCastShadows(true);
        node->attachObject(entity);
        node->scale(0.01f, 0.01f, 0.01f);
        node->setPosition(position);
        transform.setIdentity();
        transform.setOrigin(convert(node->getPosition()));

        auto rbody = mPhysics->CreateRigidBody(mShellMass, transform, shape, node,
                                               static_cast<short>(CollisionTypes::PROJECTILE),
                                               CollisionTypes::OBSTACLES |
                                               mTargetType);
        auto shell = new Shell(rbody, mWorld, mPhysics, mBlastForce, mBlastRadius);
        shell->SetLinearVelocity(convert(mProjectileVelocity));
        shell->SetGravity(btVector3(0, -mProjectileGravity, 0));
        mPool.Add(shell);

        mElapsedDelay = 0.0f;
        mProjectileVelocity = Ogre::Vector3::ZERO;
        mProjectileGravity = 0.0f;
    }
}

bool Turret::IsReady() const
{
    return mElapsedDelay >= mDelayBetweenShots;
}

void Turret::GetLookAtRotations(const Ogre::Vector3& target,
                                Ogre::Quaternion* turretRotation,
                                Ogre::Quaternion* barrelRotation) const
{
    assert(turretRotation != nullptr && barrelRotation != nullptr);

    // Get a quaternion from the direction vector
    auto lookRotation = LookRotation(target.normalisedCopy(), Ogre::Vector3::UNIT_Y);

    // Convert it to euler representation
    auto turretAngles = Ogre::Euler(lookRotation);
    auto barrelAngles = Ogre::Euler(lookRotation);

    // The turret doesn't pitch, so we use the turret's current pitch
    turretAngles.setPitch(mTurret->getOrientation().getPitch());

    // The barrel doesn't yaw and roll, so we do the same thing as ^
    barrelAngles.setYaw(mBarrel->getOrientation().getYaw());
    barrelAngles.setRoll(mBarrel->getOrientation().getRoll());

    // Clamp pitch angle for barrel
    // Because mProjectileVelocity is from the nozzle's location
    // to the target point, so we reverse the sign
    if (-lookRotation.getPitch() > Ogre::Degree(30))
    {
        barrelAngles.setPitch(Ogre::Degree(-30)); // I don't know why it's negative, need to find out
    }
    else if (-lookRotation.getPitch() < Ogre::Degree(0))
    {
        barrelAngles.setPitch(Ogre::Degree(0));
    }

    *turretRotation = turretAngles;
    *barrelRotation = barrelAngles;
}

void Turret::SmoothRotate(const Ogre::Quaternion& turretRotation,
                          const Ogre::Quaternion& barrelRotation,
                          const float& deltaTime) const
{
    mTurret->setOrientation(Ogre::Quaternion::Slerp(4.0f * deltaTime,
                                                    mTurret->getOrientation(),
                                                    turretRotation,
                                                    true));
    mBarrel->setOrientation(Ogre::Quaternion::Slerp(4.0f * deltaTime,
                                                    mBarrel->getOrientation(),
                                                    barrelRotation,
                                                    true));
}

bool Turret::FireAt(const Ogre::Vector3& target)
{
    if (IsReady())
    {
        Ogre::Vector3 s0;
        float g;
        auto position = mNozzle->_getDerivedPosition();

        // Calculate the projectile velocity
        auto hasSolution = ProjectileMath::SolveBallisticArcLateral(position,
                                                                    mShellSpeed,
                                                                    target,
                                                                    position.y + 1.0f,
                                                                    &s0,
                                                                    &g);

        mProjectileVelocity = hasSolution ? s0 : Ogre::Vector3::ZERO;
        mProjectileGravity = hasSolution ? g : 0.0f;
        return hasSolution;
    }

    // Turret is not ready to fire (on cooldown)
    return false;
}
