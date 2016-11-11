#include "SpawnState.hpp"
#include "Tank.h"
#include "WanderState.hpp"

TankState* SpawnState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    if (mMoveLocation == Ogre::Vector3::ZERO)
    {
        std::uniform_real_distribution<float> xDis(-60, 60);
        std::uniform_real_distribution<float> zDis(-70, 70);
        mMoveLocation = Ogre::Vector3(xDis(mRNG), 0, zDis(mRNG));

        // Move to location
        tank->UpdateHealthBar();
        tank->MoveTo(mMoveLocation);
    }

    if (tank->getPosition().positionEquals(mMoveLocation, 10.0f))
    {
        return new WanderState();
    }

    return nullptr;
}
