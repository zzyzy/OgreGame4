#include "Tank.h"

Tank::Tank(Ogre::SceneManager* world,
           PhysicsEngine* physics,
           Type type) :
    SceneNode(world),
    mWorld(world),
    mPhysics(physics),
    mTurretNode(nullptr),
    mBarrelNode(nullptr),
    mNozzleNode(nullptr),
    mHealthBarNode(nullptr),
    mSelectionNode(nullptr),
    mType(type),
    mMaxHitPoints(100.0f),
    mHitPoints(mMaxHitPoints),
    mTurret()
{
    assert(world != nullptr);
    assert(physics != nullptr);
}

void Tank::setTurret(Ogre::SceneNode* turret)
{
    mTurretNode = turret;
    assert(mTurretNode != nullptr);
}

void Tank::setBarrel(Ogre::SceneNode* barrel)
{
    mBarrelNode = barrel;
    assert(mBarrelNode != nullptr);
}

void Tank::setNozzle(Ogre::SceneNode* nozzle)
{
    mNozzleNode = nozzle;
    assert(mNozzleNode != nullptr);
}

void Tank::setHealthDecal(Ogre::SceneNode* healthDecal)
{
    mHealthBarNode = healthDecal;
    assert(mHealthBarNode != nullptr);
}

void Tank::setSelectionDecal(Ogre::SceneNode* selectionDecal)
{
    mSelectionNode = selectionDecal;
    assert(mSelectionNode != nullptr);
}

void Tank::setupTurretController()
{
    mTurret = Turret(mTurretNode, mBarrelNode, mNozzleNode, mWorld, mPhysics, 5);
}

Tank::Tank(const Tank& tank) :
    SceneNode(tank.mWorld),
    mWorld(tank.mWorld),
    mPhysics(tank.mPhysics),
    //mBodyNode(tank.mBodyNode),
    mTurretNode(tank.mTurretNode),
    mBarrelNode(tank.mBarrelNode),
    mNozzleNode(tank.mNozzleNode),
    mHealthBarNode(tank.mHealthBarNode),
    mSelectionNode(tank.mSelectionNode),
    mType(tank.mType),
    mMaxHitPoints(tank.mMaxHitPoints),
    mHitPoints(tank.mHitPoints),
    mTurret(tank.mTurret)
{
}

Tank::Tank(Tank&& tank) :
    SceneNode(tank.mWorld),
    mWorld(tank.mWorld),
    mPhysics(tank.mPhysics),
    //mBodyNode(tank.mBodyNode),
    mTurretNode(tank.mTurretNode),
    mBarrelNode(tank.mBarrelNode),
    mNozzleNode(tank.mNozzleNode),
    mHealthBarNode(tank.mHealthBarNode),
    mSelectionNode(tank.mSelectionNode),
    mType(tank.mType),
    mMaxHitPoints(tank.mMaxHitPoints),
    mHitPoints(tank.mHitPoints),
    mTurret(std::move(tank.mTurret))
{
}

Tank& Tank::operator=(const Tank& tank)
{
    Tank tmp(tank);
    *this = std::move(tmp);
    return *this;
}

Tank& Tank::operator=(Tank&& tank)
{
    mWorld = tank.mWorld;
    mPhysics = tank.mPhysics;
    //mBodyNode = tank.mBodyNode;
    mTurretNode = tank.mTurretNode;
    mBarrelNode = tank.mBarrelNode;
    mNozzleNode = tank.mNozzleNode;
    mHealthBarNode = tank.mHealthBarNode;
    mSelectionNode = tank.mSelectionNode;
    mType = tank.mType;
    mMaxHitPoints = tank.mMaxHitPoints;
    mHitPoints = tank.mHitPoints;
    mTurret = std::move(tank.mTurret);
    return *this;
}

//Tank::Tank(std::string name,
//           Type type,
//           Ogre::Vector3 spawnPosition,
//           Ogre::SceneManager* mSceneMgr) :
//    mTurret(nullptr),
//    mNozzleNode(nullptr)
//{
//    idName = name;
//    mType = type;
//    tankSpawnPosition = spawnPosition;
//    mWorld = mSceneMgr;
//
//    mHitPoints = 1.0;
//    mMove = 0;
//
//    mTurretRotate = 0;
//    mBarrelRotate = 0;
//    mBarrelPitch = 0;
//
//    switch (type)
//    {
//    case Type::CHALLENGER:
//        mBodyRotate = 180;
//        break;
//    case Type::LEOPARD:
//        mBodyRotate = 0;
//        break;
//    default:
//        break;
//    }
//
//    Setup();
//
//    mTurret = new Turret(mTurretNode,
//                         mBarrelNode,
//                         mNozzleNode,
//                         mWorld,
//                         mPhysics,
//                         5);
//}

//void Tank::Setup()
//{
//    switch (mType)
//    {
//    case Type::CHALLENGER:
//        {
//            idName += "Ch";
//
//            std::string bodyName = idName + "Body";
//
//            // Create tank body entity
//            Ogre::Entity* tankBody = mWorld->createEntity(bodyName, "chbody.mesh");
//            tankBody->setCastShadows(true);
//            tankBody->setMaterialName("ch_tank_material");
//            tankBody->setQueryFlags(COL_TANK);
//
//            std::string turretName = idName + "Turret";
//            // Create tank turret entity
//            Ogre::Entity* tankTurret = mWorld->createEntity(turretName, "chturret.mesh");
//            tankTurret->setCastShadows(true);
//            tankTurret->setMaterialName("ch_tank_material");
//            tankTurret->setQueryFlags(COL_TANK);
//
//            std::string barrelName = idName + "Barrel";
//            // Create tank barrel entity
//            Ogre::Entity* tankBarrel = mWorld->createEntity(barrelName, "chbarrel.mesh");
//            tankBarrel->setCastShadows(true);
//            tankBarrel->setMaterialName("ch_tank_material");
//            tankBarrel->setQueryFlags(COL_TANK);
//
//            // Create a child scene node and attach tank body to it
//            mBodyNode = mWorld->getRootSceneNode()->createChildSceneNode();
//            mBodyNode->attachObject(tankBody);
//            // Move it above the ground
//            mBodyNode->translate(tankSpawnPosition);
//            mBodyNode->scale(0.05, 0.05, 0.05);
//            //rotate
//            mBodyNode->yaw(Ogre::Degree(mBodyRotate));
//
//            // Create a child scene node from tank body's scene node and attach the tank turret to it
//            mTurretNode = mBodyNode->createChildSceneNode();
//            mTurretNode->attachObject(tankTurret);
//            // Move it above tank body
//            mTurretNode->translate(0, 3, 0);
//
//            // Create a child scene node from tank turret's scene node and attach the tank barrel to it
//            mBarrelNode = mTurretNode->createChildSceneNode();
//            mBarrelNode->attachObject(tankBarrel);
//            // Move it to the appropriate position on the turret
//            mBarrelNode->translate(-30, 10, 0);
//
//            createBillboards();
//        }
//        break;
//    case Type::LEOPARD:
//        {
//            idName += "Lp";
//
//            std::string bodyName = idName + "Body";
//            // Create tank body entity
//            Ogre::Entity* tankBody = mWorld->createEntity(bodyName, "lpbody.mesh");
//            tankBody->setCastShadows(true);
//            tankBody->setMaterialName("lp_tank_material");
//            tankBody->setQueryFlags(COL_TANK);
//
//            std::string turretName = idName + "Turret";
//            // Create tank turret entity
//            Ogre::Entity* tankTurret = mWorld->createEntity(turretName, "lpturret.mesh");
//            tankTurret->setCastShadows(true);
//            tankTurret->setMaterialName("lp_tank_material");
//            tankTurret->setQueryFlags(COL_TANK);
//
//            std::string barrelName = idName + "Barrel";
//            // Create tank barrel entity
//            Ogre::Entity* tankBarrel = mWorld->createEntity(barrelName, "lpbarrel.mesh");
//            tankBarrel->setCastShadows(true);
//            tankBarrel->setMaterialName("lp_tank_material");
//            tankBarrel->setQueryFlags(COL_TANK);
//
//            // Create a child scene node and attach tank body to it
//            mBodyNode = mWorld->getRootSceneNode()->createChildSceneNode();
//            mBodyNode->attachObject(tankBody);
//            // Move it above the ground
//            mBodyNode->translate(tankSpawnPosition);
//            mBodyNode->scale(0.05, 0.05, 0.05);
//
//            // Create a child scene node from tank body's scene node and attach the tank turret to it
//            mTurretNode = mBodyNode->createChildSceneNode();
//            mTurretNode->attachObject(tankTurret);
//            // Move it above tank body
//            mTurretNode->translate(0, 3, 0);
//
//            // Create a child scene node from tank turret's scene node and attach the tank barrel to it
//            mBarrelNode = mTurretNode->createChildSceneNode();
//            mBarrelNode->attachObject(tankBarrel);
//            // Move it to the appropriate position on the turret
//            mBarrelNode->translate(-30, 10, 0);
//
//            createBillboards();
//        }
//        break;
//    default:
//        break;
//    }
//};

//void Tank::createBillboards()
//{
//    // Create a BillboardSet to represent a health bar and set its properties
//    Ogre::BillboardSet* mHealthBar = mWorld->createBillboardSet();
//    mHealthBar->setCastShadows(false);
//    mHealthBar->setDefaultDimensions(50, 2.0);
//    mHealthBar->setMaterialName("myMaterial/HealthBar");
//
//    // Create a billboard for the health bar BillboardSet
//    Ogre::Billboard* mHealthBarBB = mHealthBar->createBillboard(Ogre::Vector3(0, 70, 0));
//    // Calculate the health bar adjustments
//    float healthBarAdjuster = (1.0 - mHitPoints) / 2; // This must range from 0.0 to 0.5
//    // Set the health bar to the appropriate level
//    mHealthBarBB->setTexcoordRect(0.0 + healthBarAdjuster, 0.0, 0.5 + healthBarAdjuster, 1.0);
//
//    // Set it to always draw on top of other objects
//    mHealthBar->setRenderQueueGroup(Ogre::RENDER_QUEUE_OVERLAY);
//
//    // Create a BillboardSet for a selection circle and set its properties
//    Ogre::BillboardSet* mSelectionCircle = mWorld->createBillboardSet();
//    mSelectionCircle->setCastShadows(false);
//    mSelectionCircle->setDefaultDimensions(200, 200);
//    mSelectionCircle->setMaterialName("myMaterial/SelectionCircle");
//    mSelectionCircle->setBillboardType(Ogre::BillboardType::BBT_PERPENDICULAR_COMMON);
//    mSelectionCircle->setCommonDirection(Ogre::Vector3(0, 1, 0));
//    mSelectionCircle->setCommonUpVector(Ogre::Vector3(0, 0, -1));
//
//    // Create a billboard for the selection circle BillboardSet
//    Ogre::Billboard* mSelectionCircleBB = mSelectionCircle->createBillboard(Ogre::Vector3(0, -19, 0));
//    mSelectionCircleBB->setTexcoordRect(0.0, 0.0, 1.0, 1.0);
//
//    std::string healthName = idName + "health";
//    std::string circleName = idName + "circle";
//    //attach billboards to the tank node
//    mHealthBarNode = mTurretNode->createChildSceneNode(healthName);
//    mHealthBarNode->attachObject(mHealthBar);
//    mHealthBarNode->setVisible(false);
//    mSelectionNode = mTurretNode->createChildSceneNode(circleName);
//    mSelectionNode->attachObject(mSelectionCircle);
//    mSelectionNode->setVisible(false);
//}

//void Tank::moveTank(float time)
//{
//    mMove = time;
//    // Move the tank
//    mBodyNode->translate(mMove, 0, 0, Ogre::Node::TransformSpace::TS_LOCAL);
//}
//
//void Tank::rotateTank(float degree)
//{
//    mBodyRotate = degree;
//    // Rotate the tank
//    mBodyNode->yaw(Ogre::Degree(mBodyRotate));
//}
//
//void Tank::rotateBarrel(float degree)
//{
//    mBarrelRotate = degree;
//    // Clamp tank barrel rotation between 0 and 30 degrees
//    if (mBarrelPitch > 30)
//        mBarrelPitch = 30;
//    else if (mBarrelPitch < 0)
//        mBarrelPitch = 0;
//    else
//        mBarrelNode->roll(Ogre::Degree(-mBarrelRotate));
//}
//
//void Tank::pitchBarrel(float degree)
//{
//    mBarrelPitch = degree;
//    // Calculate the tank barrel's current pitch
//    mBarrelPitch += mBarrelRotate;
//}
//
//void Tank::rotateTurret(float degree)
//{
//    mTurretRotate = degree;
//    // Rotate the tank turret
//    mTurretNode->yaw(Ogre::Degree(mTurretRotate));
//}


bool Tank::isTankSelected()
{
    if (mSelectionNode->getAttachedObject(0)->isVisible())
        return true;

    return false;
}

void Tank::setBillboardsVisible(bool isVisible)
{
    mSelectionNode->setVisible(isVisible);
    mHealthBarNode->setVisible(isVisible);
}

void Tank::UpdateHealthBar() const
{
    // Calculate the health bar adjustments
    auto healthBarAdjuster = (1.0f - (mHitPoints / mMaxHitPoints)) / 2.0f; // This must range from 0.0 to 0.5
    auto healthBar = static_cast<Ogre::BillboardSet*>(mHealthBarNode->getAttachedObject(0));
    auto healthBarBB = healthBar->getBillboard(0);

    // Set the health bar to the appropriate level
    healthBarBB->setTexcoordRect(0.0f + healthBarAdjuster, 0.0f, 0.5f + healthBarAdjuster, 1.0f);
}

void Tank::Update(const float& deltaTime)
{
    mTurret.Update(deltaTime);
}

void Tank::FireAt(const Ogre::Vector3& target)
{
    mTurret.FireAt(target);
}

void Tank::ApplyDamage(const float& damage)
{
    mHitPoints -= damage;
}

float Tank::TotalDamageReceived()
{
    return mMaxHitPoints - mHitPoints;
}
