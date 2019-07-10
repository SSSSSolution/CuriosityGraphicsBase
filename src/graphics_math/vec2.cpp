#include <cmath>
#include "vec2.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Vec2::Vec2(float x, float y)
        : x(x), y(y) {
    }

    Vec2 Vec2::normalize() const {
        float sum = x * x + y * y;
        return Vec2(x < 0 ? -1.0f * sqrt(x * x / sum) : sqrt(x * x / sum),
                    y < 0 ? -1.0f * sqrt(y * y / sum) : sqrt(y * y / sum));
    }

    Vec2 Vec2::operator -(const Vec2 &other) const {
        Vec2 ret(x - other.x, y - other.y);
        return ret;
    }

    Vec2 Vec2::operator -=(const Vec2 &other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vec2 Vec2::operator +(const Vec2 &other) const {
        Vec2 ret(x + other.x, y + other.y);
        return ret;
    }

    Vec2 Vec2::operator +=(const Vec2 &other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vec2 Vec2::operator *(float v) const {
        Vec2 ret(x * v, y * v);
        return ret;
    }

    float Vec2::dot(const Vec2 &other) const {
        return x * other.x + y * other.y;
    }

    }
}
