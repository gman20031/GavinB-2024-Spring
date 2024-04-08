#pragma once

class IUseable
{
public:
    virtual ~IUseable() = default;
    virtual void Use() = 0;
};