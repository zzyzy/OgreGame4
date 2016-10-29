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
    mMoveSpeed(25.0f),
    mDamage(50.0f),
    mAttackSpeed(1.0f),
    mTurnRate(5.0f),
    mTurret(),
    mKinematic()
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
    mTurret = Turret(mTurretNode, mBarrelNode, mNozzleNode, mWorld, mPhysics, 5,
                     1, 250, 2, 0.5, 10);
}

void Tank::setupKinematicController(Ogre::ManualObject* pathViz, btPairCachingGhostObject* collider)
{
    mKinematic = TankKinematics(this, pathViz, collider);
}

Tank::Tank(const Tank& tank) :
    SceneNode(tank.mWorld),
    mWorld(tank.mWorld),
    mPhysics(tank.mPhysics),
    mTurretNode(tank.mTurretNode),
    mBarrelNode(tank.mBarrelNode),
    mNozzleNode(tank.mNozzleNode),
    mHealthBarNode(tank.mHealthBarNode),
    mSelectionNode(tank.mSelectionNode),
    mType(tank.mType),
    mMaxHitPoints(tank.mMaxHitPoints),
    mHitPoints(tank.mHitPoints),
    mMoveSpeed(tank.mMoveSpeed),
    mDamage(tank.mDamage),
    mAttackSpeed(tank.mAttackSpeed),
    mTurnRate(tank.mTurnRate),
    mTurret(tank.mTurret),
    mKinematic(tank.mKinematic)
{
}

Tank::Tank(Tank&& tank) :
    SceneNode(tank.mWorld),
    mWorld(tank.mWorld),
    mPhysics(tank.mPhysics),
    mTurretNode(tank.mTurretNode),
    mBarrelNode(tank.mBarrelNode),
    mNozzleNode(tank.mNozzleNode),
    mHealthBarNode(tank.mHealthBarNode),
    mSelectionNode(tank.mSelectionNode),
    mType(tank.mType),
    mMaxHitPoints(tank.mMaxHitPoints),
    mHitPoints(tank.mHitPoints),
    mMoveSpeed(tank.mMoveSpeed),
    mDamage(tank.mDamage),
    mAttackSpeed(tank.mAttackSpeed),
    mTurnRate(tank.mTurnRate),
    mTurret(std::move(tank.mTurret)),
    mKinematic(std::move(tank.mKinematic))
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
    mTurretNode = tank.mTurretNode;
    mBarrelNode = tank.mBarrelNode;
    mNozzleNode = tank.mNozzleNode;
    mHealthBarNode = tank.mHealthBarNode;
    mSelectionNode = tank.mSelectionNode;
    mType = tank.mType;
    mMaxHitPoints = tank.mMaxHitPoints;
    mHitPoints = tank.mHitPoints;
    mMoveSpeed = tank.mMoveSpeed;
    mDamage = tank.mDamage;
    mAttackSpeed = tank.mAttackSpeed;
    mTurnRate = tank.mTurnRate;
    mTurret = std::move(tank.mTurret);
    mKinematic = std::move(tank.mKinematic);
    return *this;
}

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
    mKinematic.Update(2.0f, deltaTime);
}

void Tank::MoveTo(const Ogre::Vector3& target, Graph* graph, PathFinding& pathFinder)
{
    mKinematic.MoveTo(target, graph, pathFinder);
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
