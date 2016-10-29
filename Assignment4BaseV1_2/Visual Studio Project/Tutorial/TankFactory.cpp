/*
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 */

#include "TankFactory.hpp"
#include "QueryMasks.hpp"
#include "CollisionMasks.hpp"

Tank* TankFactory::MakeChallengerTank(const Ogre::Vector3& position) const
{
    auto bodyEntity = mWorld->createEntity("chbody.mesh");
    auto turretEntity = mWorld->createEntity("chturret.mesh");
    auto barrelEntity = mWorld->createEntity("chbarrel.mesh");
    auto nozzleEntity = mWorld->createEntity("sphere.mesh");

    auto tank = OGRE_NEW Tank(mWorld,
                              mPhysics,
                              Tank::Type::CHALLENGER);
    mWorld->getRootSceneNode()->addChild(tank);
    auto turretNode = tank->createChildSceneNode();
    auto barrelNode = turretNode->createChildSceneNode();
    auto nozzleNode = barrelNode->createChildSceneNode();

    auto bodyChild = tank->createChildSceneNode();
    auto turretChild = turretNode->createChildSceneNode();
    auto barrelChild = barrelNode->createChildSceneNode();
    auto nozzleChild = nozzleNode->createChildSceneNode();

    // Body settings
    bodyEntity->setCastShadows(true);
    bodyEntity->setMaterialName("ch_tank_material");
    bodyEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TANK));
    bodyChild->attachObject(bodyEntity);
    bodyChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));

    // Turret settings
    turretEntity->setCastShadows(true);
    turretEntity->setMaterialName("ch_tank_material");
    turretEntity->setQueryFlags(0);
    turretChild->attachObject(turretEntity);
    turretChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    turretNode->translate(0, 3, 0);

    // Barrel settings
    barrelEntity->setCastShadows(true);
    barrelEntity->setMaterialName("ch_tank_material");
    barrelEntity->setQueryFlags(0);
    barrelChild->attachObject(barrelEntity);
    barrelChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    barrelNode->translate(0, 12, 36);

    // Nozzle settings
    nozzleEntity->setCastShadows(true);
    nozzleEntity->setQueryFlags(0);
    nozzleChild->attachObject(nozzleEntity);
    nozzleChild->scale(0.05f, 0.05f, 0.05f);
    nozzleNode->translate(0, 0, 60);
    nozzleNode->setVisible(false);

    // Scale the whole tank (this makes it equal to leopard tank)
    tank->scale(0.25f, 0.25f, 0.25f);

    // Create a BillboardSet to represent a health bar and set its properties
    auto healthBar = mWorld->createBillboardSet();
    healthBar->setCastShadows(false);
    healthBar->setQueryFlags(0);
    healthBar->setDefaultDimensions(50, 2.0f);
    healthBar->setMaterialName("myMaterial/HealthBar");

    // Create a billboard for the health bar BillboardSet
    auto healthBarBB = healthBar->createBillboard(Ogre::Vector3(0, 70, 0));
    // Calculate the health bar adjustments
    auto healthBarAdjuster = (1.0f - 0.0f) / 2.0f; // This must range from 0.0 to 0.5
    // Set the health bar to the appropriate level
    healthBarBB->setTexcoordRect(0.0f + healthBarAdjuster, 0.0f, 0.5f + healthBarAdjuster, 1.0f);

    // Set it to always draw on top of other objects
    healthBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

    // Create a BillboardSet for a selection circle and set its properties
    auto selectionCircle = mWorld->createBillboardSet();
    selectionCircle->setCastShadows(false);
    selectionCircle->setQueryFlags(0);
    selectionCircle->setDefaultDimensions(200, 200);
    selectionCircle->setMaterialName("myMaterial/SelectionCircle");
    selectionCircle->setBillboardType(Ogre::BillboardType::BBT_PERPENDICULAR_COMMON);
    selectionCircle->setCommonDirection(Ogre::Vector3(0, 1, 0));
    selectionCircle->setCommonUpVector(Ogre::Vector3(0, 0, -1));

    // Create a billboard for the selection circle BillboardSet
    auto selectionCircleBB = selectionCircle->createBillboard(Ogre::Vector3(0, -19, 0));
    selectionCircleBB->setTexcoordRect(0, 0, 1, 1);

    auto healthBarNode = turretNode->createChildSceneNode();
    healthBarNode->attachObject(healthBar);
    healthBarNode->setVisible(false);
    auto selectionNode = turretNode->createChildSceneNode();
    selectionNode->attachObject(selectionCircle);
    selectionNode->setVisible(false);

    // Scale the tank again (from now it should be same as leopard tank)
    tank->scale(0.25f, 0.25f, 0.25f);
    tank->setPosition(position);

    // Prepare ghost object (collider)
    btTransform startTrans;
    startTrans.setIdentity();
    startTrans.setRotation(convert(tank->getOrientation()));
    startTrans.setOrigin(convert(tank->getPosition()));
    auto group = static_cast<short>(CollisionTypes::CH_TANK);
    auto mask = CollisionTypes::TANK |
        CollisionTypes::GROUND |
        CollisionTypes::OBSTACLES |
        CollisionTypes::POWERUP |
        CollisionTypes::EXPLOSION |
        CollisionTypes::PROJECTILE;
    auto shape = new btBoxShape(btVector3(0.1f * 50, 0.1f * 50, 0.1f * 50));
    auto collider = mPhysics->CreateGhostObject(startTrans,
                                                shape,
                                                group,
                                                mask);
    collider->setCollisionFlags(collider->getCollisionFlags() |
        btCollisionObject::CF_KINEMATIC_OBJECT);

    // Prepare path visualizer
    auto pathViz = mWorld->createManualObject();
    pathViz->clear();
    pathViz->setDynamic(true);
    pathViz->setQueryFlags(0);
    mWorld->getRootSceneNode()->createChildSceneNode()->attachObject(pathViz);
    pathViz->getParentSceneNode()->setVisible(true);

    // Set tank settings
    tank->setTurret(turretNode);
    tank->setBarrel(barrelNode);
    tank->setNozzle(nozzleNode);
    tank->setHealthDecal(healthBarNode);
    tank->setSelectionDecal(selectionNode);
    tank->setupTurretController(CollisionTypes::LP_TANK);
    tank->setupKinematicController(pathViz, collider);

    return tank;
}

Tank* TankFactory::MakeLeopardTank(const Ogre::Vector3& position) const
{
    auto bodyEntity = mWorld->createEntity("lpbody.mesh");
    auto turretEntity = mWorld->createEntity("lpturret.mesh");
    auto barrelEntity = mWorld->createEntity("lpbarrel.mesh");
    auto nozzleEntity = mWorld->createEntity("sphere.mesh");

    auto tank = OGRE_NEW Tank(mWorld,
                              mPhysics,
                              Tank::Type::LEOPARD);
    mWorld->getRootSceneNode()->addChild(tank);
    auto turretNode = tank->createChildSceneNode();
    auto barrelNode = turretNode->createChildSceneNode();
    auto nozzleNode = barrelNode->createChildSceneNode();

    auto bodyChild = tank->createChildSceneNode();
    auto turretChild = turretNode->createChildSceneNode();
    auto barrelChild = barrelNode->createChildSceneNode();
    auto nozzleChild = nozzleNode->createChildSceneNode();

    // Body settings
    bodyEntity->setCastShadows(true);
    bodyEntity->setMaterialName("lp_tank_material");
    bodyEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TANK));
    bodyChild->attachObject(bodyEntity);
    bodyChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));

    // Turret settings
    turretEntity->setCastShadows(true);
    turretEntity->setMaterialName("lp_tank_material");
    turretEntity->setQueryFlags(0);
    turretChild->attachObject(turretEntity);
    turretChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    turretNode->translate(0, 1, 0);

    // Barrel settings
    barrelEntity->setCastShadows(true);
    barrelEntity->setMaterialName("lp_tank_material");
    barrelEntity->setQueryFlags(0);
    barrelChild->attachObject(barrelEntity);
    barrelChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    barrelNode->translate(-1.25f, 12, 30);

    // Nozzle settings
    nozzleEntity->setCastShadows(true);
    nozzleEntity->setQueryFlags(0);
    nozzleChild->attachObject(nozzleEntity);
    nozzleChild->scale(0.05f, 0.05f, 0.05f);
    nozzleNode->translate(0.75f, 0, 40);
    nozzleNode->setVisible(false);

    // Scale the whole tank
    tank->scale(0.33f, 0.33f, 0.33f);

    // Create a BillboardSet to represent a health bar and set its properties
    auto healthBar = mWorld->createBillboardSet();
    healthBar->setCastShadows(false);
    healthBar->setQueryFlags(0);
    healthBar->setDefaultDimensions(50, 2.0f);
    healthBar->setMaterialName("myMaterial/HealthBar");

    // Create a billboard for the health bar BillboardSet
    auto healthBarBB = healthBar->createBillboard(Ogre::Vector3(0, 70, 0));
    // Calculate the health bar adjustments
    auto healthBarAdjuster = (1.0f - 0.0f) / 2.0f; // This must range from 0.0 to 0.5
    // Set the health bar to the appropriate level
    healthBarBB->setTexcoordRect(0.0f + healthBarAdjuster, 0.0f, 0.5f + healthBarAdjuster, 1.0f);

    // Set it to always draw on top of other objects
    healthBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);

    // Create a BillboardSet for a selection circle and set its properties
    auto selectionCircle = mWorld->createBillboardSet();
    selectionCircle->setCastShadows(false);
    selectionCircle->setQueryFlags(0);
    selectionCircle->setDefaultDimensions(200, 200);
    selectionCircle->setMaterialName("myMaterial/SelectionCircle");
    selectionCircle->setBillboardType(Ogre::BillboardType::BBT_PERPENDICULAR_COMMON);
    selectionCircle->setCommonDirection(Ogre::Vector3(0, 1, 0));
    selectionCircle->setCommonUpVector(Ogre::Vector3(0, 0, -1));

    // Create a billboard for the selection circle BillboardSet
    auto selectionCircleBB = selectionCircle->createBillboard(Ogre::Vector3(0, -19, 0));
    selectionCircleBB->setTexcoordRect(0, 0, 1, 1);

    auto healthBarNode = turretNode->createChildSceneNode();
    healthBarNode->attachObject(healthBar);
    healthBarNode->setVisible(false);
    auto selectionNode = turretNode->createChildSceneNode();
    selectionNode->attachObject(selectionCircle);
    selectionNode->setVisible(false);

    // Scale the tank again
    tank->scale(0.25f, 0.25f, 0.25f);
    tank->setPosition(position);

    // Prepare collider
    btTransform startTrans;
    startTrans.setIdentity();
    startTrans.setRotation(convert(tank->getOrientation()));
    startTrans.setOrigin(convert(tank->getPosition()));
    auto group = static_cast<short>(CollisionTypes::LP_TANK);
    auto mask = CollisionTypes::TANK |
        CollisionTypes::GROUND |
        CollisionTypes::OBSTACLES |
        CollisionTypes::POWERUP |
        CollisionTypes::EXPLOSION |
        CollisionTypes::PROJECTILE;
    auto shape = new btBoxShape(btVector3(0.1f * 50, 0.1f * 50, 0.1f * 50));
    auto collider = mPhysics->CreateGhostObject(startTrans,
                                                shape,
                                                group,
                                                mask);
    collider->setCollisionFlags(collider->getCollisionFlags() |
        btCollisionObject::CF_KINEMATIC_OBJECT);

    // Prepare path visualizer
    auto pathViz = mWorld->createManualObject();
    pathViz->clear();
    pathViz->setDynamic(true);
    pathViz->setQueryFlags(0);
    mWorld->getRootSceneNode()->createChildSceneNode()->attachObject(pathViz);
    pathViz->getParentSceneNode()->setVisible(true);

    // Set tank settings
    tank->setTurret(turretNode);
    tank->setBarrel(barrelNode);
    tank->setNozzle(nozzleNode);
    tank->setHealthDecal(healthBarNode);
    tank->setSelectionDecal(selectionNode);
    tank->setupTurretController(CollisionTypes::CH_TANK);
    tank->setupKinematicController(pathViz, collider);

    return tank;
}
