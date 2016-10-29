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

class Tank : public Ogre::SceneNode,
             public IDamageableObject
{
public:
    friend class TankFactory;

    enum class Type
    {
        CHALLENGER,
        LEOPARD
    };

    Tank(const Tank& tank);

    Tank(Tank&& tank);

    Tank& operator=(const Tank& tank);

    Tank& operator=(Tank&& tank);

    //helper function for selection
    bool isTankSelected();

    void setBillboardsVisible(bool isVisible);

    //tank updates
    void UpdateHealthBar() const;

    void Update(const float& deltaTime);

    void FireAt(const Ogre::Vector3& target);

    // IDamageableObject
    void ApplyDamage(const float& damage) override;

    float TotalDamageReceived() override;

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

    // Getters for tank details
    float GetMaxHitPoints() const { return mMaxHitPoints; }
    float GetHitPoints() const { return mHitPoints; }
    float GetMoveSpeed() const { return mMoveSpeed; }
    float GetAttackDamage() const { return mDamage; }
    float GetAttackSpeed() const { return mAttackSpeed; }

    // Setters for tank details
    void SetMaxHitPoints(const float& maxHP) { mMaxHitPoints = maxHP; }
    void SetHitPoints(const float& hp) { mHitPoints = hp; }
    void SetMoveSpeed(const float& ms) { mMoveSpeed = ms; }
    void SetAttackDamage(const float& damage) { mDamage = damage; }
    void SetAttackSpeed(const float& as) { mAttackSpeed = as; }

private:
    //void createBillboards();

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
    void setupTurretController();

    // Scene manager and physics engine reference
    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;

    // Scene nodes for the different tank parts
    //Ogre::SceneNode* mBodyNode;
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
    float mMoveSpeed;       // Move speed factor (1.0f = normal movespeed, 1.25 = 25% faster?)
    float mDamage;          // Damage dealt to other tanks (if damage > maxHP) = enemy dies
    float mAttackSpeed;     // Delay between shots in seconds for the turret

    // Controllers
    Turret mTurret;

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
