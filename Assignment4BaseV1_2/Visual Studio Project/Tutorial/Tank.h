/*
 * Tank class
 *
 * Copyright (C) 2016 Ivana Ozakovic, Zhen Zhi Lee
 * Written by Ivana Ozakovic, Zhen Zhi Lee
 * 
 * TODO Add description
 */

#pragma once
#ifndef __TANK_H__
#define __TANK_H__

#include "Turret.hpp"
#include "IDamageableObject.hpp"
#include "TankKinematics.hpp"
#include "TankStateMachine.hpp"
#include "PowerUpEffect.hpp"

class Tank : public Ogre::SceneNode,
             public IDamageableObject,
             public IPoolObject
{
public:
    friend class TankFactory;

    enum class Type
    {
        CHALLENGER,
        LEOPARD
    };

    //helper function for selection
    bool isTankSelected();

    void setBillboardsVisible(bool isVisible);

    //tank updates
    void UpdateHealthBar() const;

    void Update(const float& deltaTime) override;

    bool MoveTo(const Ogre::Vector3& target);

    void Stop() { mKinematic.ClearPaths(); }

    void FireAt(const Ogre::Vector3& target);

    // IDamageableObject
    void ApplyDamage(const float& damage) override;

    float TotalDamageReceived() override;

    Ogre::SceneNode* GetNearestObject() const;

    //Tank(std::string name,
    //     Type type,
    //     Ogre::Vector3 spawnPosition,
    //     Ogre::SceneManager* mSceneMgr);

    //tank movements
    /*void moveTank(float time);
    void rotateTank(float degree);
    void rotateBarrel(float degree);
    void pitchBarrel(float degree);
    void rotateTurret(float degree);*/

    //helper function in case any of the nodes needed
    Ogre::SceneNode* getTankHealthNode() { return mHealthBarNode; };
    Ogre::SceneNode* getTankSelectionNode() { return mSelectionNode; };
    Ogre::SceneNode* getTankBaseNode() { return this; };
    Ogre::SceneNode* getTankTurretNode() { return mTurretNode; };
    Ogre::SceneNode* getTankBarrelNode() { return mBarrelNode; };

    //helper functions to get attributes
    /*std::string getTankName() { return idName; };
    Type getTankType() { return mType; };*/

    //void Setup();
    Type GetType() const { return mType; }

    // Getters for tank details
    float GetMaxHitPoints() const { return mMaxHitPoints; }
    float GetHitPoints() const { return mHitPoints; }
    float GetMoveSpeed() const { return mMoveSpeed; }
    float GetAttackDamage() const { return mDamage; }
    float GetAttackSpeed() const { return mAttackSpeed; }
    float GetTurnRate() const { return mTurnRate; }
    float GetScanRange() const { return mScanRange; }
    float GetScore() const { return mScore; }

    // Setters for tank details
    void SetMaxHitPoints(const float& maxHP) { mMaxHitPoints = maxHP; }
    void SetHitPoints(const float& hp) { mHitPoints = hp; }
    void SetMoveSpeed(const float& ms) { mMoveSpeed = ms; }
    void SetAttackDamage(const float& damage) { mDamage = damage; }
    void SetAttackSpeed(const float& as) { mAttackSpeed = as; }
    void SetTurnRate(const float& rate) { mTurnRate = rate; }
    void SetScanRange(const float& range) { mScanRange = range; }
    void AddScore(const float& score) { mScore += score; }

    void AddPowerUpEffect(PowerUpEffect* effect) { mPowerUpPool.Add(effect); }

    float* GetMaxHPPtr() { return &mMaxHitPoints; }
    float* GetHPPtr() { return &mHitPoints; }
    float* GetMSPtr() { return &mMoveSpeed; }
    float* GetDamagePtr() { return &mDamage; }
    float* GetASPtr() { return &mAttackSpeed; }

    // Is this object disposable?
    bool IsDisposable() const override
    {
        return mHitPoints < 0;
    }

    // Is this object disposed?
    bool IsDisposed() const override
    {
        return mIsDisposed;
    }

    // Dispose this object, basically cleaning up
    // and release any unused memory/dangling pointers
    void Dispose() override;

private:
    // Only allow instantialisation via TankFactory
    Tank(Ogre::SceneManager* world,
         PhysicsEngine* physics,
         Type type);

    // Helper methods for TankFactory
    void setTurret(Ogre::SceneNode* turret);
    void setBarrel(Ogre::SceneNode* barrel);
    void setNozzle(Ogre::SceneNode* nozzle);
    void setHealthDecal(Ogre::SceneNode* healthDecal);
    void setSelectionDecal(Ogre::SceneNode* selectionDecal);
    void setPathFinding(Graph* graph, PathFinding* pathFinder);
    void setupTurretController(const CollisionTypes& targetType);
    void setupKinematicController(Ogre::ManualObject* pathViz, btPairCachingGhostObject* collider);
    void setupStateMachine();

    // Scene manager and physics engine reference
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
    Graph* mGraph;
    PathFinding* mPathFinder;

    // Scene nodes for the different tank parts
    Ogre::SceneNode* mTurretNode;
    Ogre::SceneNode* mBarrelNode;
    Ogre::SceneNode* mNozzleNode;

    // Scene nodes for decal
    Ogre::SceneNode* mHealthBarNode;
    Ogre::SceneNode* mSelectionNode;

    // Tank details
    Type mType;
    float mMaxHitPoints;    // Max hit points
    float mHitPoints;       // Hit points (if it reaches 0 it means this tank is dead)
    float mMoveSpeed;       // Move speed
    float mDamage;          // Damage dealt to other tanks (if damage > maxHP) = enemy dies
    float mAttackSpeed;     // Delay between shots in seconds for the turret
    float mTurnRate;
    float mScanRange;
    float mScore;
    bool mIsDisposed;

    // Controllers
    Turret mTurret;
    TankKinematics mKinematic;
    TankStateMachine mState;

    // Powerups
    PoolManager mPowerUpPool;

    //Ogre::Vector3 tankSpawnPosition;

    //Billboards
    //Billboard nodes

    // For tank movement and rotation
    //float mMove;
    //float mBodyRotate;
    //float mTurretRotate;
    //float mBarrelRotate;
    //float mBarrelPitch;

    //health 
    //float mHitPoints;

    //Tank attributes
    //std::string idName;
};

#endif // __TANK_H__
