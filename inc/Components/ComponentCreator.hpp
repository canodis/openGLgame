#pragma once

#include "Component.hpp"
#include "GravityComponent.hpp"

class ComponentCreator
{
public:
    template <typename T>
    static Component *Create()
    {
        return (new T());
    }
};