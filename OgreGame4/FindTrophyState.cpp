#include "FindTrophyState.hpp"
#include <random>
#include "Tank.h"
#include "WanderState.hpp"

TankState* FindTrophyState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    //if (mMoveLocation == Ogre::Vector3::ZERO)
    //{
    //    mMoveLocation = mTrophy->getPosition();

    //    // Move to location
    //    if (!mMoveLocation.positionCloses(mTrophy->getPosition(), 5.0f))
    //        tank->MoveTo(mMoveLocation);
    //}

    if (tank->getPosition().positionEquals(mTrophy->getPosition(), 5.0f))
    {
        return new WanderState();
    } 
    
    if (!tank->MoveTo(mTrophy->getPosition()))
    {
        return new WanderState();
    }

    return nullptr;
}
