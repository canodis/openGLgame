#include <tuple>

namespace dis
{
    class ivec2
    {
    public:
        int x;
        int y;

        ivec2(int x, int y)
        {
            this->x = x;
            this->y = y;
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
    };
}