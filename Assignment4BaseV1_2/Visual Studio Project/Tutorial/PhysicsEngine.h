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

private:
	btDefaultCollisionConfiguration*		mCollisionConfiguration;
	btCollisionDispatcher*					mDispatcher;
	btBroadphaseInterface*					mBroadphase;
	btSequentialImpulseConstraintSolver*	mSolver;
	btDiscreteDynamicsWorld*				mDynamicsWorld;

	//keep the collision shapes, for deletion/cleanup
	btAlignedObjectArray<btCollisionShape*>	mCollisionShapes;
};

#endif