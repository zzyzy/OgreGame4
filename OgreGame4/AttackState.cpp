#include "AttackState.hpp"
#include "WanderState.hpp"
#include "Tank.h"

TankState* AttackState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    Tank* tank = tankState.GetTank();

    tank->FireAt(mAttackLoc);

    return new WanderState();
}
