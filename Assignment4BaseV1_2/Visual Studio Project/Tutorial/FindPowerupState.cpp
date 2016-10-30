#include "FindPowerupState.hpp"
#include "WanderState.hpp"

TankState* FindPowerupState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    if (!mPowerUp)
    {
        return new WanderState();
    }

    if (mMoveLocation == Ogre::Vector3::ZERO)
    {
        mMoveLocation = mPowerUp->getPosition();

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
