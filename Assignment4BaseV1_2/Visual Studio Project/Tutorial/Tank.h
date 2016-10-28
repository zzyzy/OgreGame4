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
#include "IDamageable.hpp"

class Tank : public Ogre::SceneNode,
             public IDamageable
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

    // IDamageable
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

private:
    //void createBillboards();

    // Only allow instantialisation via TankFactory
    Tank(Ogre::SceneManager* world,
         PhysicsEngine* physics,
         Type type);

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
    float mMaxHitPoints;
    float mHitPoints;

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
