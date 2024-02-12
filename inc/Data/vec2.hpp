#pragma once

#include "ivec2.hpp"
#include <math.h>

namespace dis
{
    class vec2
    {
    public:
        float x;
        float y;

        vec2()
        {
            x = 0.0f;
            y = 0.0f;
        }

        vec2(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        vec2& operator=(const vec2 &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }

        vec2 operator=(const ivec2 &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }

        bool operator<(const vec2 &rhs) const
        {
            return x < rhs.x && y < rhs.y;
        }

        bool operator==(const vec2 &rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const vec2 &rhs) const
        {
            return x != rhs.x && y != rhs.y;
        }

        bool operator>(const vec2 &rhs) const
        {
            return x > rhs.x && y > rhs.y;
        }

        bool operator<=(const vec2 &rhs) const
        {
            return x <= rhs.x && y <= rhs.y;
        }

        bool operator>=(const vec2 &rhs) const
        {
            return x >= rhs.x && y >= rhs.y;
        }

        void operator+=(const vec2 &rhs)
        {
            x += rhs.x;
            y += rhs.y;
        }

        void operator-=(const vec2 &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
        }

        vec2 operator-(const vec2 &rhs) const
        {
            return vec2(x - rhs.x, y - rhs.y);
        }

        vec2 operator+(const vec2 &rhs) const
        {
            return vec2(x + rhs.x, y + rhs.y);
        }

        vec2 operator*(const vec2 &rhs) const
        {
            return vec2(x * rhs.x, y * rhs.y);
        }

        vec2 operator/(const vec2 &rhs) const
        {
            return vec2(x / rhs.x, y / rhs.y);
        }

        vec2 operator*(float rhs) const
        {
            return vec2(x * rhs, y * rhs);
        }

        void normalize()
        {
            float length = sqrt(x * x + y * y);
            x /= length;
            y /= length;
        }

        vec2 operator-(const ivec2 &rhs) const
        {
            return vec2(x - rhs.x, y - rhs.y);
        }

    };
}
