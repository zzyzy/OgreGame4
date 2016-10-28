/*
 * Base class for all entities
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Adapted from Unity3D GameObject class
 * https://docs.unity3d.com/ScriptReference/GameObject.html
 */

#pragma once
#ifndef __GAME_OBJECT_HPP__
#define __GAME_OBJECT_HPP__

#include "Component.hpp"

class GameObject
{
public:
    virtual ~GameObject()
    {
        for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
        {
            delete it->second;
        }

        mComponents.clear();
    }

    virtual void UpdateAll(const float& deltaTime) final
    {
        for (auto it = mComponents.begin(); it != mComponents.end(); ++it)
        {
            it->second->Update(deltaTime);
        }
    }

    virtual void AddComponent(Component* component) final
    {
        auto p = mComponents.insert(std::make_pair(component->GetTypeName(), component));
        assert(p.second == true);
    }

    virtual Component* GetComponent(std::string componentName) final
    {
        return mComponents[componentName];
    }

private:
    std::unordered_map<std::string, Component*> mComponents;
};

#endif // __GAME_OBJECT_HPP__
