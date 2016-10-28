/*
 * Pool manager
 * 
 * Copyright (C) 2016 Zhen Zhi Lee
 * Written by Zhen Zhi Lee (leezhenzhi@gmail.com)
 * 
 * Manages a collection of objects that implements
 * the interface IPoolObject.
 */

#pragma once
#ifndef __POOL_MANAGER_HPP__
#define __POOL_MANAGER_HPP__

#include "IPoolObject.hpp"
#include "PoolObject.hpp"

class PoolManager
{
public:
    PoolManager(const size_t& maxPoolSize = 5);

    ~PoolManager();

    PoolManager(const PoolManager& other);

    PoolManager(PoolManager&& other);

    PoolManager& operator=(const PoolManager& other);

    PoolManager& operator=(PoolManager&& other);

    void Update(const float& deltaTime);

    void Add(PoolObject* object);

    void Remove(PoolObject* object);

    size_t CurrentSize() const;

    size_t MaxSize() const;

private:
    size_t mMaxPoolSize;
    std::set<PoolObject*> mPool;
};

#endif // __POOL_MANAGER_HPP__
