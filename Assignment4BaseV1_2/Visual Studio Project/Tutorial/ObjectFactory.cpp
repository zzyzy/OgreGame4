#include "ObjectFactory.hpp"
#include "QueryMasks.hpp"
#include "CollisionMasks.hpp"

Trophy* ObjectFactory::MakeTrophy(const Ogre::Vector3& position) const
{
    auto entity = mWorld->createEntity("cube.mesh");
    auto trophy = OGRE_NEW Trophy(mWorld);
    auto scale = Ogre::Vector3(0.02f, 0.02f, 0.02f);
    mWorld->getRootSceneNode()->addChild(trophy);
    entity->setCastShadows(true);
    entity->setQueryFlags(static_cast<Ogre::uint32>(QueryTypes::TROPHY));
    trophy->attachObject(entity);
    trophy->scale(scale);
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
