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
    TANK        = 1 << 1,
    OBSTACLES   = 1 << 2,
    POWERUP     = 1 << 3,
    EXPLOSION   = 1 << 4,
    PROJECTILE  = 1 << 5
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
