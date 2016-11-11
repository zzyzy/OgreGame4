#include "DestroyedState.hpp"
#include "Tank.h"
#include "SpawnState.hpp"

TankState* DestroyedState::Update(TankStateMachine& tankState, const float& deltaTime)
{
    if (mTimer < mRespawnTime)
    {
        mTimer += deltaTime;
    } else
    {
        Tank* tank = tankState.GetTank();

        // Either we move the tank somewhere or 
        // destroy it and create a new one
        //tank->setPosition();

        return new SpawnState();
    }

    return nullptr;
}
