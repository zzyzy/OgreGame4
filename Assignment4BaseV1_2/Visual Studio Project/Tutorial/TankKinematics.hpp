/*
 * Controls the movement of the tank
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Adapted from
 * http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Intermediate+Tutorial+1
 */

#pragma once
#ifndef __TANK_KINEMATICS_HPP__
#define __TANK_KINEMATICS_HPP__

#include "Graph.h"
#include "PathFinding.h"
#include "PhysicsEngine.h"

// Prevent circular reference
class Tank;

class TankKinematics
{
public:
    TankKinematics();

    ~TankKinematics();

    TankKinematics(Tank* tank,
                   Ogre::SceneManager* world,
                   PhysicsEngine* physics,
                   Ogre::ManualObject* pathViz,
                   btPairCachingGhostObject* collider);

    TankKinematics(const TankKinematics& other);

    TankKinematics(TankKinematics&& other);

    TankKinematics& operator=(const TankKinematics& other);

    TankKinematics& operator=(TankKinematics&& other);

    // Pathfinding
    bool MoveTo(const Ogre::Vector3& target, Graph* graph, PathFinding& pathFinder);

    void SetPath(const std::deque<Ogre::Vector3>& path)
    {
        mPath = path;
    }

    void AddNode(const Ogre::Vector3& location)
    {
        mPath.push_back(location);
    }

    bool IsPathEmpty() const
    {
        return mPath.empty();
    }

    Ogre::Vector3 GetLastNode() const
    {
        return mPath.back();
    }

    // Seeking
    static Ogre::Vector3 Seek(const Ogre::Vector3& from, const Ogre::Vector3& target,
                              const float& speed, const Ogre::Vector3& currentVelocity);

    static btVector3 Seek(const btVector3& from, const btVector3& target,
                          const float& speed, const btVector3& currentVelocity);

    bool HasSeekTarget() const
    {
        return mSeekTarget != nullptr;
    }

    bool CanSeekTarget(float minDistance) const;

    void SetSeekTarget(Ogre::SceneNode* target);

    // These should be called every frame
    void SeekTarget(Graph& graph, PathFinding& pathFinder);

    void Update(const float& minDistance, const float& deltaTime);

    // Path visualizer
    Ogre::ManualObject* GetPathVisualizer() const
    {
        return mPathVisualizer;
    }

    void BuildPathVisualizer();

    void ClearPaths()
    {
        mPath.clear();
    }

    void ShowPathVisualizer(bool show = true) const
    {
        mPathVisualizer->getParentSceneNode()->setVisible(show);
    }

    void TogglePathVisualizer();

private:
    bool nextLocation();

    Ogre::SceneManager* mWorld;
    PhysicsEngine* mPhysics;
    Tank* mTank; // Reference to tank
    Ogre::ManualObject* mPathVisualizer; // Path visualizer
    btPairCachingGhostObject* mCollider; // Collider
    Ogre::ColourValue mPathVizColour; // Path visualizer colour
    std::deque<Ogre::Vector3> mPath; // Path to follow
    Ogre::Real mDistance; // Distance between current position and destination
    Ogre::Vector3 mDestination; // Destination taken from the path
    Ogre::Vector3 mDirection; // Direction towards the destination
    Ogre::SceneNode* mSeekTarget; // Target to seek
    bool mShowPathViz; // Whether to show path visualizer or not
};

#endif // __TANK_KINEMATICS_HPP__
