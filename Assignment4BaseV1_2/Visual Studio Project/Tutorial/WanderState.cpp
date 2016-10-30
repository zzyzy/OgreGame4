#include "WanderState.hpp"
#include "Tank.h"
#include "AttackState.hpp"
#include "Trophy.hpp"
#include "FindTrophyState.hpp"
#include "PowerUp.h"
#include "FindPowerupState.hpp"

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

    auto object = tank->GetNearestObject();
    auto trophy = dynamic_cast<Trophy*>(object);
    auto enemyTank = dynamic_cast<Tank*>(object);
    auto powerup = dynamic_cast<PowerUp*>(object);

    if (enemyTank && 
        enemyTank->GetType() != tank->GetType() &&
        !enemyTank->getPosition().positionEquals(tank->getPosition(), 10.0f))
    {
        tank->Stop();
        return new AttackState(enemyTank->getPosition());
    }

    if (trophy)
    {
        tank->Stop();
        return new FindTrophyState(trophy);
    }

    if (powerup)
    {
        tank->Stop();
        return new FindPowerupState(powerup);
    }

    if (tank->getPosition().positionEquals(mMoveLocation, 10.0f))
    {
        mMoveLocation = Ogre::Vector3::ZERO;
    }

    return nullptr;
}
