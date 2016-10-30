#include "WanderState.hpp"
#include "Tank.h"
#include "AttackState.hpp"
#include "Trophy.hpp"
#include "FindTrophyState.hpp"

TankState* WanderState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    if (mMoveLocation == Ogre::Vector3::ZERO)
    {
        std::uniform_real_distribution<float> xDis(-60, 60);
        std::uniform_real_distribution<float> zDis(-70, 70);
        mMoveLocation = Ogre::Vector3(xDis(mRNG), 0, zDis(mRNG));

        // Move to location
        tank->MoveTo(mMoveLocation);
    }

    if (tank->getPosition().positionEquals(mMoveLocation, 10.0f))
    {
        mMoveLocation = Ogre::Vector3::ZERO;
    }

    auto object = tank->GetNearestObject();
    auto trophy = dynamic_cast<Trophy*>(object);
    auto enemyTank = dynamic_cast<Tank*>(object);

    if (trophy)
    {
        return new FindTrophyState(trophy);
    }

    if (enemyTank && enemyTank->GetType() != tank->GetType())
    {
        return new AttackState();
    }

    return nullptr;
}
