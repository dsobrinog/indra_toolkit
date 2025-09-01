#pragma once

#include "imgui.h"

class IPositionable
{
public:
    virtual ~IPositionable() = default;

    virtual void GetPosition() = 0;
    virtual void SetPosition() = 0;

    virtual void GetSize() = 0;
    virtual void SetSize() = 0;

    virtual void ApplyLayout() = 0;
};