#pragma once

#include "Component.hpp"

class ComponentCreator
{
public:
    template <typename T>
    static Component *Create()
    {
        return (new T());
    }
};