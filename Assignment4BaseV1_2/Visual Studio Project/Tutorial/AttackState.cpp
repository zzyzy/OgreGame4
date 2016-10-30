#include "AttackState.hpp"
#include "WanderState.hpp"
#include "Tank.h"

TankState* AttackState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    auto object = tank->GetNearestObject();
    auto enemyTank = dynamic_cast<Tank*>(object);
    if (enemyTank && enemyTank->GetType() != tank->GetType())
    {
        tank->FireAt(enemyTank->getPosition());
    }
    else
    {
        return new WanderState();
    }

    return nullptr;
}
