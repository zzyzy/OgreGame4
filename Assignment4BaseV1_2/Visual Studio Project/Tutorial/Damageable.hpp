#pragma once
#ifndef __DAMAGEABLE_HPP__
#define __DAMAGEABLE_HPP__

#include "Component.hpp"
#include "IDamageable.hpp"

class Damageable : public Component, public IDamageable
{
public:
    void ApplyDamage(const float& damage) override = 0;

    float TotalDamageReceived() override = 0;
};

#endif // __DAMAGEABLE_HPP__
