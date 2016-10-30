#include "FindTrophyState.hpp"
#include <random>
#include "Tank.h"
#include "WanderState.hpp"

TankState* FindTrophyState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    if (mMoveLocation == Ogre::Vector3::ZERO)
    {
        std::uniform_real_distribution<float> xDis(-60, 60);
        std::uniform_real_distribution<float> zDis(-70, 70);
        mMoveLocation = mTrophy->getPosition();

        // Move to location
        tank->MoveTo(mMoveLocation);
    }

    if (tank->getPosition().positionEquals(mMoveLocation, 10.0f))
    {
        mMoveLocation = Ogre::Vector3::ZERO;
        return new WanderState();
    }

    return nullptr;
}
