/*
 * Query masks for this game
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Intermediate+Tutorial+4
 */

#pragma once
#ifndef __QUERY_MASKS_HPP__
#define __QUERY_MASKS_HPP__

enum class QueryTypes
{
    NOTHING     = 0,
    GROUND      = 1 << 0,
    TANK        = 1 << 1,
    OBSTACLES   = 1 << 2
};

inline Ogre::uint32 operator|(QueryTypes left, QueryTypes right)
{
    return static_cast<Ogre::uint32>(left) | static_cast<Ogre::uint32>(right);
}

inline short operator|(short left, const QueryTypes& right)
{
    return left | static_cast<short>(right);
}

#endif // __QUERY_MASKS_HPP__