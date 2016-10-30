/*
 * Collision masks for this game
 *
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * http://www.bulletphysics.org/mediawiki-1.5.8/index.php/Collision_Filtering
 */

#pragma once
#ifndef __COLLISION_MASKS_HPP__
#define __COLLISION_MASKS_HPP__

enum class CollisionTypes
{
    NOTHING     = 0,
    GROUND      = 1 << 0,
    OBSTACLES   = 1 << 1,
    POWERUP     = 1 << 2,
    EXPLOSION   = 1 << 3,
    PROJECTILE  = 1 << 4,
    LP_TANK     = 1 << 5,
    CH_TANK     = 1 << 6,
    TROPHY      = 1 << 7,
    TANK        = LP_TANK | CH_TANK
};

inline short operator|(const CollisionTypes& left, const CollisionTypes& right)
{
    return static_cast<short>(left) | static_cast<short>(right);
}

inline short operator|(short left, const CollisionTypes& right)
{
    return left | static_cast<short>(right);
}

#endif // __COLLISION_MASKS_HPP__
