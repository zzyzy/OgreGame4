#ifndef __PHYSICSENGINE_H
#define __PHYSICSENGINE_H

#include "stdafx.h"
#include "Utilities.h"

class PhysicsEngine
{
public:
    PhysicsEngine();
    ~PhysicsEngine();

    void initPhysics();
    void exitPhysics();
    void update(float deltaTime);
    btRigidBody* createRigidBody(float mass, const btTransform& startTransform, btCollisionShape* collisionShape, Ogre::SceneNode* node);
    void destroyRigidBody(btRigidBody* rigidBody);
    btCollisionObject* checkForCollision(btCollisionObject* object);

    // Create rigidbody with specified collision group and mask
    btRigidBody* CreateRigidBody(const float& mass, const btTransform& startTrans,
                                 btCollisionShape* collisionShape,
                                 Ogre::SceneNode* node,
                                 short group,
                                 short mask);

    // GhostObject
    void AddGhostObject(btPairCachingGhostObject* go,
                        const btTransform& startTrans,
                        btCollisionShape* collisionShape,
                        short filterGroup,
                        short filterMask);
    btPairCachingGhostObject* CreateGhostObject(const btTransform& startTrans,
                                                btCollisionShape* collisionShape,
                                                short filterGroup = btBroadphaseProxy::DefaultFilter,
                                                short filterMask = btBroadphaseProxy::AllFilter);
    void DestroyGhostObject(btPairCachingGhostObject* ghostObject);

    // RigidBody collision detection
    btCollisionObject* GetCollidedObject(btCollisionObject* object) const;
    std::set<btCollisionObject*> GetAllCollidedObjects(btCollisionObject* object) const;

    // GhostObject collision detection
    std::set<btCollisionObject*> GetAllCollidedObjects(btPairCachingGhostObject* object) const;

    // Apply impulse via raycasting
    void ShootRay(const btVector3& rayFromWorld, const btVector3& rayToWorld, const btVector3& impulse) const;

private:
    btDefaultCollisionConfiguration* mCollisionConfiguration;
    btCollisionDispatcher* mDispatcher;
    btBroadphaseInterface* mBroadphase;
    btSequentialImpulseConstraintSolver* mSolver;
    btDiscreteDynamicsWorld* mDynamicsWorld;

    //keep the collision shapes, for deletion/cleanup
    btAlignedObjectArray<btCollisionShape*> mCollisionShapes;
};

#endif
