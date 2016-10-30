#pragma once
#ifndef __TANK_COLLIDER_HPP__
#define __TANK_COLLIDER_HPP__

class Tank;

class TankCollider : public btPairCachingGhostObject
{
public:
    explicit TankCollider(Tank* tank)
        : mTank(tank)
    {
    }

    void SetTank(Tank* tank) { mTank = tank; }
        
    Tank* GetTank() const { return mTank; }

private:
    Tank* mTank;
};

#endif // __TANK_COLLIDER_HPP__