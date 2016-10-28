/*
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 */

#include "TankFactory.hpp"
#include "QueryMasks.hpp"

Tank* TankFactory::MakeChallengerTank(const Ogre::Vector3& position) const
{
    auto bodyEntity = mWorld->createEntity("chbody.mesh");
    auto turretEntity = mWorld->createEntity("chturret.mesh");
    auto barrelEntity = mWorld->createEntity("chbarrel.mesh");
    auto nozzleEntity = mWorld->createEntity("sphere.mesh");

    Tank* tank = OGRE_NEW Tank(mWorld,
                               mPhysics,
                               Tank::Type::CHALLENGER);
    mWorld->getRootSceneNode()->addChild(tank);
    //auto bodyNode = OGRE_NEW Ogre::SceneNode(mWorld);
    //auto bodyNode = mWorld->getRootSceneNode()->createChildSceneNode();
    auto turretNode = tank->createChildSceneNode();
    auto barrelNode = turretNode->createChildSceneNode();
    auto nozzleNode = barrelNode->createChildSceneNode();

    auto bodyChild = tank->createChildSceneNode();
    auto turretChild = turretNode->createChildSceneNode();
    auto barrelChild = barrelNode->createChildSceneNode();
    auto nozzleChild = nozzleNode->createChildSceneNode();

    bodyEntity->setCastShadows(true);
    bodyEntity->setMaterialName("ch_tank_material");
    bodyEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TANK));
    bodyChild->attachObject(bodyEntity);
    bodyChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));

    turretEntity->setCastShadows(true);
    turretEntity->setMaterialName("ch_tank_material");
    //turretEntity->setQueryFlags(COL_TANK);
    turretChild->attachObject(turretEntity);
    turretChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    turretNode->translate(0, 3, 0);

    barrelEntity->setCastShadows(true);
    barrelEntity->setMaterialName("ch_tank_material");
    //barrelEntity->setQueryFlags(COL_TANK);
    barrelChild->attachObject(barrelEntity);
    barrelChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    barrelNode->translate(0, 12, 36);

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

    // Set tank settings
    tank->setTurret(turretNode);
    tank->setBarrel(barrelNode);
    tank->setNozzle(nozzleNode);
    tank->setHealthDecal(healthBarNode);
    tank->setSelectionDecal(selectionNode);
    tank->setupTurretController();
    tank->scale(0.25f, 0.25f, 0.25f);
    tank->setPosition(position);

    return tank;
}

Tank* TankFactory::MakeLeopardTank(const Ogre::Vector3& position) const
{
    auto bodyEntity = mWorld->createEntity("lpbody.mesh");
    auto turretEntity = mWorld->createEntity("lpturret.mesh");
    auto barrelEntity = mWorld->createEntity("lpbarrel.mesh");
    auto nozzleEntity = mWorld->createEntity("sphere.mesh");

    Tank* tank = OGRE_NEW Tank(mWorld,
                               mPhysics,
                               Tank::Type::LEOPARD);
    mWorld->getRootSceneNode()->addChild(tank);
    //auto bodyNode = OGRE_NEW Ogre::SceneNode(mWorld);
    //auto bodyNode = mWorld->getRootSceneNode()->createChildSceneNode();
    auto turretNode = tank->createChildSceneNode();
    auto barrelNode = turretNode->createChildSceneNode();
    auto nozzleNode = barrelNode->createChildSceneNode();

    auto bodyChild = tank->createChildSceneNode();
    auto turretChild = turretNode->createChildSceneNode();
    auto barrelChild = barrelNode->createChildSceneNode();
    auto nozzleChild = nozzleNode->createChildSceneNode();

    bodyEntity->setCastShadows(true);
    bodyEntity->setMaterialName("lp_tank_material");
    bodyEntity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TANK));
    bodyChild->attachObject(bodyEntity);
    bodyChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));

    turretEntity->setCastShadows(true);
    turretEntity->setMaterialName("lp_tank_material");
    //turretEntity->setQueryFlags(COL_TANK);
    turretChild->attachObject(turretEntity);
    turretChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    turretNode->translate(0, 1, 0);

    barrelEntity->setCastShadows(true);
    barrelEntity->setMaterialName("lp_tank_material");
    //barrelEntity->setQueryFlags(COL_TANK);
    barrelChild->attachObject(barrelEntity);
    barrelChild->rotate(Ogre::Vector3::UNIT_Y, Ogre::Degree(90));
    barrelNode->translate(-1.25f, 12, 30);

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

    // Set tank settings
    tank->setTurret(turretNode);
    tank->setBarrel(barrelNode);
    tank->setNozzle(nozzleNode);
    tank->setHealthDecal(healthBarNode);
    tank->setSelectionDecal(selectionNode);
    tank->setupTurretController();
    tank->scale(0.25f, 0.25f, 0.25f);
    tank->setPosition(position);

    return tank;
}
