#include "ObjectFactory.hpp"
#include "QueryMasks.hpp"
#include "CollisionMasks.hpp"

Trophy* ObjectFactory::MakeTrophy(const Ogre::Vector3& position, float* lpScore, float* chScore) const
{
    auto entity = mWorld->createEntity("cube.mesh");
    auto trophy = OGRE_NEW Trophy(mWorld, mPhysics, lpScore, chScore);
    auto scale = Ogre::Vector3(0.02f, 0.02f, 0.02f);
    mWorld->getRootSceneNode()->addChild(trophy);
    auto child = trophy->createChildSceneNode();
    entity->setCastShadows(true);
    entity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TROPHY));
    child->attachObject(entity);
    child->scale(scale);
    trophy->setPosition(position);

    btTransform startTransform;
    auto shape = new btBoxShape(btVector3(scale.x * 50, scale.y * 50, scale.z * 50));
    short group = static_cast<short>(CollisionTypes::TROPHY);
    short mask = CollisionTypes::TANK |
        CollisionTypes::GROUND;
    startTransform.setIdentity();
    startTransform.setOrigin(convert(trophy->getPosition()));
    auto rbody = mPhysics->CreateRigidBody(1.0f, startTransform, shape, trophy, group, mask);

    trophy->SetRBody(rbody);

    return trophy;
}

PowerUp* ObjectFactory::MakePowerUp(const Ogre::Vector3& position, PowerUp::Type type) const
{
    auto entity = mWorld->createEntity("PowerUp.mesh");
    auto powerup = OGRE_NEW PowerUp(mWorld, mPhysics, type);
    auto scale = Ogre::Vector3(2.0f, 2.0f, 2.0f);
    mWorld->getRootSceneNode()->addChild(powerup);
    auto child = powerup->createChildSceneNode();
    entity->setCastShadows(true);
    entity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::POWERUP));

    switch (type)
    {
    case PowerUp::Type::HealthBoost:
        entity->setMaterialName("HealthPowerUp");
        break;
    case PowerUp::Type::SpeedBoost:
        entity->setMaterialName("SpeedPowerUp");
        break;
    case PowerUp::Type::DamageBoost:
        entity->setMaterialName("FirePowerUp");
        break;
    case PowerUp::Type::AttackSpeedBoost:
        entity->setMaterialName("RatePowerUp");
        break;
    default:
        break;
    }

    child->attachObject(entity);
    child->scale(scale);
    powerup->setPosition(position);

    btTransform startTransform;
    auto shape = new btBoxShape(btVector3(scale.x, scale.y, scale.z));
    short group = static_cast<short>(CollisionTypes::POWERUP);
    short mask = CollisionTypes::TANK |
        CollisionTypes::GROUND;
    startTransform.setIdentity();
    startTransform.setOrigin(convert(powerup->getPosition()));
    auto rbody = mPhysics->CreateRigidBody(1.0f, startTransform, shape, powerup, group, mask);

    powerup->SetRBody(rbody);

    return powerup;
}
