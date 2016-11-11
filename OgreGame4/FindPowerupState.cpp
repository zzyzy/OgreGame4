#include "FindPowerupState.hpp"
#include "WanderState.hpp"

TankState* FindPowerupState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();


    if (tank->getPosition().positionEquals(mPowerUp->getPosition(), 5.0f))
    {
        return new WanderState();
    }

    if (!tank->MoveTo(mPowerUp->getPosition()))
    {
        return new WanderState();
    }


    return nullptr;
}
