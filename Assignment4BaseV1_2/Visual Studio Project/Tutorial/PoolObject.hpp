#pragma once

#include "Component.hpp"
#include "IPoolObject.hpp"
#include "IFrameUpdate.hpp"

class PoolObject : public Component, public IPoolObject
{
public:
    friend class PoolManager;

    PoolObject(IPoolObject* poolObject, IFrameUpdate* frameUpdate) :
        mPoolObject(poolObject),
        mFrameUpdate(frameUpdate)
    {
        assert(poolObject != nullptr);
    }

    void Update(const float& deltaTime) override
    {
        mFrameUpdate->Update(deltaTime);
    }

    std::string GetTypeName() const override
    {
        return typeid(PoolObject).name();
    }

    bool IsDisposable() const override
    {
        return mPoolObject->IsDisposable();
    }

    bool IsDisposed() const override
    {
        return mPoolObject->IsDisposed();
    }

    void Dispose() override
    {
        mPoolObject->Dispose();
    }

private:
    IPoolObject* mPoolObject;
    IFrameUpdate* mFrameUpdate;
};
