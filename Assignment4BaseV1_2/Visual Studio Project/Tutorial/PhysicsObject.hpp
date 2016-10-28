#pragma once

#include "Component.hpp"
#include "IPhysicsObject.hpp"

class PhysicsObject : public Component
{
public:
    PhysicsObject(PhysicsEngine* physics,
                  btRigidBody* rbody,
                  IPhysicsObject* physicsObject) :
        mPhysics(physics),
        mRBody(rbody),
        mPhysicsObject(physicsObject)
    {
        assert(physics != nullptr);
        assert(rbody != nullptr);
        assert(physicsObject != nullptr);
    }

    btRigidBody*& GetRBody()
    {
        return mRBody;
    }

    PhysicsEngine* GetPhyEngine() const
    {
        return mPhysics;
    }

    std::string GetTypeName() const override
    {
        return typeid(PhysicsObject).name();
    }

private:
    PhysicsEngine* mPhysics;
    btRigidBody* mRBody;
    IPhysicsObject* mPhysicsObject;
};
