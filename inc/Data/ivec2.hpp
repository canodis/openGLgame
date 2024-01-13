#pragma once
#include <tuple>

namespace dis
{
    class ivec2
    {
    public:
        int x;
        int y;

        ivec2()
        {
            x = 0;
            y = 0;
        }

        ivec2(int x, int y)
        {
            this->x = x;
            this->y = y;
        }

        ivec2& operator=(const ivec2 &rhs)
        {
            x = rhs.x;
            y = rhs.y;
            return *this;
        }

        bool operator<(const ivec2 &rhs) const
        {
            return std::tie(x, y) < std::tie(rhs.x, rhs.y);
        }

        bool operator==(const ivec2 &rhs) const
        {
            return std::tie(x, y) == std::tie(rhs.x, rhs.y);
        }

        bool operator!=(const ivec2 &rhs) const
        {
            return std::tie(x, y) != std::tie(rhs.x, rhs.y);
        }

        bool operator>(const ivec2 &rhs) const
        {
            return std::tie(x, y) > std::tie(rhs.x, rhs.y);
        }

        bool operator<=(const ivec2 &rhs) const
        {
            return std::tie(x, y) <= std::tie(rhs.x, rhs.y);
        }

        bool operator>=(const ivec2 &rhs) const
        {
            return std::tie(x, y) >= std::tie(rhs.x, rhs.y);
        }

        void operator+=(const ivec2 &rhs)
        {
            x += rhs.x;
            y += rhs.y;
        }

        void operator-=(const ivec2 &rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
        }
    };
}