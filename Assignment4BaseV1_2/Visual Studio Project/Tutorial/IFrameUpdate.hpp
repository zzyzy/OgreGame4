#pragma once

class IFrameUpdate
{
public:
    virtual ~IFrameUpdate()
    {
    }

    virtual void Update(const float& deltaTime) = 0;
};
