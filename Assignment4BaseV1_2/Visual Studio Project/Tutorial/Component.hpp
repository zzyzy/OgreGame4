/*
 * Base class for everything attached to GameObjects
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Adapted from Unity3D Component class.
 * https://docs.unity3d.com/ScriptReference/Component.html
 */

#pragma once
#ifndef __COMPONENT_HPP__
#define __COMPONENT_HPP__

class Component
{
public:
    virtual ~Component()
    {
    }

    virtual void Update(const float& deltaTime)
    {
    }

    virtual std::string GetTypeName() const = 0;
};

#endif // __COMPONENT_HPP__
