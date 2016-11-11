/*
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 */

#include "TankKinematics.hpp"
#include "Tank.h"
#include "OgreEuler.hpp"

TankKinematics::TankKinematics() :
    mTank(nullptr),
    mWorld(nullptr),
    mPhysics(nullptr),
    mPathVisualizer(nullptr),
    mCollider(nullptr),
    mPathVizColour(0, 1, 0, 1),
    mDistance(0),
    mDestination(Ogre::Vector3::ZERO),
    mDirection(Ogre::Vector3::ZERO),
    mSeekTarget(nullptr),
    mShowPathViz(true)
{
}

TankKinematics::~TankKinematics()
{
    if (mPathVisualizer)
    {
        mPathVisualizer->getParentSceneNode()->detachObject(mPathVisualizer);
        mWorld->destroyManualObject(mPathVisualizer);
    }

    if (mCollider)
        mPhysics->DestroyGhostObject(mCollider);
}

TankKinematics::TankKinematics(Tank* tank,
                               Ogre::SceneManager* world,
                               PhysicsEngine* physics,
                               Ogre::ManualObject* pathViz,
                               btPairCachingGhostObject* collider) :
    mTank(tank),
    mWorld(world),
    mPhysics(physics),
    mPathVisualizer(pathViz),
    mCollider(collider),
    mPathVizColour(0, 1, 0, 1),
    mDistance(0),
    mDestination(Ogre::Vector3::ZERO),
    mDirection(Ogre::Vector3::ZERO),
    mSeekTarget(nullptr),
    mShowPathViz(true)
{
}

TankKinematics::TankKinematics(const TankKinematics& other) :
    mTank(other.mTank),
    mWorld(other.mWorld),
    mPhysics(other.mPhysics),
    mPathVisualizer(other.mPathVisualizer),
    mCollider(other.mCollider),
    mPathVizColour(other.mPathVizColour),
    mDistance(other.mDistance),
    mDestination(other.mDestination),
    mDirection(other.mDirection),
    mSeekTarget(other.mSeekTarget),
    mShowPathViz(other.mShowPathViz)
{
}

TankKinematics::TankKinematics(TankKinematics&& other) :
    mTank(other.mTank),
    mWorld(other.mWorld),
    mPhysics(other.mPhysics),
    mPathVisualizer(other.mPathVisualizer),
    mCollider(other.mCollider),
    mPathVizColour(other.mPathVizColour),
    mDistance(other.mDistance),
    mDestination(other.mDestination),
    mDirection(other.mDirection),
    mSeekTarget(other.mSeekTarget),
    mShowPathViz(other.mShowPathViz)
{
    other.mPathVisualizer = nullptr;
    other.mCollider = nullptr;
}

TankKinematics& TankKinematics::operator=(const TankKinematics& other)
{
    TankKinematics tmp(other);
    *this = std::move(tmp);
    return *this;
}

TankKinematics& TankKinematics::operator=(TankKinematics&& other)
{
    if (mPathVisualizer)
    {
        mPathVisualizer->getParentSceneNode()->detachObject(mPathVisualizer);
        mWorld->destroyManualObject(mPathVisualizer);
    }

    if (mCollider)
        mPhysics->DestroyGhostObject(mCollider);

    mTank = other.mTank;
    mWorld = other.mWorld;
    mPhysics = other.mPhysics;
    mPathVisualizer = other.mPathVisualizer;
    mCollider = other.mCollider;
    mPathVizColour = other.mPathVizColour;
    mDistance = other.mDistance;
    mDirection = other.mDirection;
    mDestination = other.mDestination;
    mSeekTarget = other.mSeekTarget;
    mShowPathViz = other.mShowPathViz;

    other.mPathVisualizer = nullptr;
    other.mCollider = nullptr;

    return *this;
}

bool TankKinematics::MoveTo(const Ogre::Vector3& target, Graph* graph, PathFinding& pathFinder)
{
    bool hasPath = false;

    if (HasSeekTarget())
    {
        SetSeekTarget(nullptr);
    }

    ClearPaths();

    int startNode = graph->getNode(mTank->getPosition());
    int goalNode = graph->getNode(target);

    // check that goal node is not the same as start node
    if (goalNode != startNode)
    {
        // try to find path from start to goal node
        std::deque<int> path;
        hasPath = pathFinder.AStar(startNode, goalNode, *graph, path);
        // if path exists
        if (hasPath)
        {
            path.pop_front();

            for (auto p : path)
            {
                auto pos = graph->getPosition(p);
                pos.y = 1.0f;
                AddNode(pos);
            }

            BuildPathVisualizer();
        }
    }

    return hasPath;
}

Ogre::Vector3 TankKinematics::Seek(const Ogre::Vector3& from, const Ogre::Vector3& target, const float& speed, const Ogre::Vector3& currentVelocity)
{
    auto desiredVelocity = target - from;
    desiredVelocity.normalise();
    desiredVelocity *= speed;
    return desiredVelocity - currentVelocity;
}

btVector3 TankKinematics::Seek(const btVector3& from, const btVector3& target, const float& speed, const btVector3& currentVelocity)
{
    auto desiredVelocity = target - from;
    desiredVelocity.normalize();
    desiredVelocity *= speed;
    return desiredVelocity - currentVelocity;
}

bool TankKinematics::CanSeekTarget(float minDistance) const
{
    if (mSeekTarget == nullptr) return false;
    if (mDirection != Ogre::Vector3::ZERO) return false;
    auto distance = (mSeekTarget->getPosition() - mTank->getPosition()).length();
    return distance > minDistance;
}

void TankKinematics::SetSeekTarget(Ogre::SceneNode* target)
{
    if (target == mTank) return;
    mSeekTarget = target;
}

void TankKinematics::SeekTarget(Graph& graph, PathFinding& pathFinder)
{
    Ogre::Vector3 location = mSeekTarget->getPosition();
    int startNode;
    int goalNode;

    if (!mPath.empty() && location != mPath.back())
    {
        mPath.clear();
    }

    startNode = graph.getNode(mTank->getPosition());
    goalNode = graph.getNode(location);

    // check that goal node is not the same as start node
    if (goalNode != startNode)
    {
        // try to find path from start to goal node
        std::deque<int> path;

        // if path exists
        if (pathFinder.AStar(startNode, goalNode, graph, path))
        {
            path.pop_front();
            path.pop_back();

            for (auto p : path)
            {
                auto pos = graph.getPosition(p);
                pos.y = 1.0f;
                AddNode(pos);
            }

            BuildPathVisualizer();
        }
    }
}

void TankKinematics::Update(const float& minDistance, const float& deltaTime)
{
    if (mDirection == Ogre::Vector3::ZERO)
    {
        if (nextLocation())
        {
            // Do something here (like activating animations)
        }
    }
    else
    {
        mDistance = (mDestination - mTank->getPosition()).length();

        if (mDistance <= minDistance)
        {
            mDirection = Ogre::Vector3::ZERO;

            if (!nextLocation())
            {
                mPathVisualizer->clear();
            }
            else
            {
                auto lookAt = LookRotation(mDirection, Ogre::Vector3::UNIT_Y);
                mTank->setOrientation(Ogre::Quaternion::Slerp(deltaTime * mTank->GetTurnRate(),
                                                              mTank->getOrientation(),
                                                              lookAt,
                                                              true));
            }
        }
        else
        {
            auto lookAt = LookRotation(mDirection, Ogre::Vector3::UNIT_Y);
            mTank->setOrientation(Ogre::Quaternion::Slerp(deltaTime * mTank->GetTurnRate(),
                                                          mTank->getOrientation(),
                                                          lookAt,
                                                          true));
            if (mTank->getOrientation().equals(lookAt, Ogre::Degree(2.5f)))
            {
                mTank->translate(Ogre::Vector3(0, 0, deltaTime * mTank->GetMoveSpeed()), Ogre::Node::TS_LOCAL);
                btTransform transform = mCollider->getWorldTransform();
                transform.setOrigin(convert(mTank->getPosition()));
                mCollider->setWorldTransform(transform);
            }
        }
    }

    // Do something else here (like adding animation frame time)
}

void TankKinematics::BuildPathVisualizer()
{
    mPathVisualizer->clear();

    // Specify the material and rendering type
    mPathVisualizer->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

    for (auto pos : mPath)
    {
        pos.y = 1.0f;
        mPathVisualizer->position(pos);
        mPathVisualizer->colour(mPathVizColour);
    }

    // Finished defining line
    mPathVisualizer->end();
}

void TankKinematics::TogglePathVisualizer()
{
    mShowPathViz = !mShowPathViz;
    mPathVisualizer->getParentSceneNode()->setVisible(mShowPathViz);
}

bool TankKinematics::nextLocation()
{
    if (mPath.empty()) return false;
    BuildPathVisualizer();
    mDestination = mPath.front(); // this gets the front of the deque
    mPath.pop_front(); // this removes the front of the deque
    auto position = mTank->getPosition();
    mDestination.y = position.y;
    mDirection = mDestination - position;
    mDistance = mDirection.normalise();
    return true;
}
