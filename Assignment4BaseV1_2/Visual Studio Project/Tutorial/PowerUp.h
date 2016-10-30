#pragma once

#include "IPoolObject.hpp"
#include "PhysicsEngine.h"
#include "TankCollider.hpp"

class PowerUp : public Ogre::SceneNode, public IPoolObject
{
public:
    enum class Type
    {
        HealthBoost,
        SpeedBoost,
        DamageBoost,
        AttackSpeedBoost
    };

    PowerUp(Ogre::SceneManager* creator, PhysicsEngine* physics, Type type) :
        SceneNode(creator),
        mCollider(nullptr),
        mPhysics(physics),
        mType(type),
        mIsDisposable(false),
        mIsDisposed(false)
    {
        assert(creator != nullptr);
        assert(physics != nullptr);
    }

    void SetCollider(btPairCachingGhostObject* collider) { mCollider = collider; }
    btPairCachingGhostObject* GetCollider() const { return mCollider; }

    // Allow the pool manager to update the pool object
    void Update(const float& deltaTime) override
    {
        auto co = mPhysics->GetCollidedObject(mCollider);

        if (co)
        {
            auto tankCol = dynamic_cast<TankCollider*>(co);

            if (tankCol)
            {
                auto tank = tankCol->GetTank();

                switch (mType)
                {
                case Type::HealthBoost:
                    tank->AddPowerUpEffect(
                        new PowerUpEffect(tank->GetMaxHitPoints(),
                                          tank->GetMaxHitPoints() + 100,
                                          5,
                                          tank->GetMaxHPPtr()));
                    tank->AddPowerUpEffect(
                        new PowerUpEffect(tank->GetHitPoints(),
                                          tank->GetHitPoints() + 100,
                                          5,
                                          tank->GetHPPtr()));
                    break;
                case Type::AttackSpeedBoost:
                    tank->AddPowerUpEffect(
                        new PowerUpEffect(tank->GetAttackSpeed(),
                                          tank->GetAttackSpeed() * 0.5f,
                                          5,
                                          tank->GetASPtr()));
                    break;
                case Type::DamageBoost:
                    tank->AddPowerUpEffect(
                        new PowerUpEffect(tank->GetAttackDamage(),
                                          tank->GetAttackDamage() * 1.25f,
                                          5,
                                          tank->GetDamagePtr()));
                    break;
                case Type::SpeedBoost:
                    tank->AddPowerUpEffect(
                        new PowerUpEffect(tank->GetMoveSpeed(),
                                          tank->GetMoveSpeed() * 2.0f,
                                          5,
                                          tank->GetMSPtr()));
                    break;
                default:
                    break;
                }

                mIsDisposable = true;
            }
        }
    }

    // Is this object disposable?
    bool IsDisposable() const override
    {
        return mIsDisposable;
    }

    // Is this object disposed?
    bool IsDisposed() const override
    {
        return mIsDisposed;
    }

    // Dispose this object, basically cleaning up
    // and release any unused memory/dangling pointers
    void Dispose() override
    {
        mPhysics->DestroyGhostObject(mCollider);
        mIsDisposed = true;
    }

private:
    btPairCachingGhostObject* mCollider;
    PhysicsEngine* mPhysics;
    Type mType;
    bool mIsDisposable;
    bool mIsDisposed;
};
