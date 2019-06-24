#include <cmath>
#include "vec2.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Vec2::Vec2(float x, float y)
        : x_(x), y_(y) {
    }

    Vec2 Vec2::normalize() const {
        float sum = x_ * x_ + y_ * y_;
        return Vec2(x_ < 0 ? -1.0f * sqrt(x_ * x_ / sum) : sqrt(x_ * x_ / sum),
                    y_ < 0 ? -1.0f * sqrt(y_ * y_ / sum) : sqrt(y_ * y_ / sum));
    }

    Vec2 Vec2::operator -(const Vec2 &other) const {
        Vec2 ret(x_ - other.x_, y_ - other.y_);
        return ret;
    }

    Vec2 Vec2::operator -=(const Vec2 &other) {
        x_ -= other.x_;
        y_ -= other.y_;
        return *this;
    }

    Vec2 Vec2::operator +(const Vec2 &other) const {
        Vec2 ret(x_ + other.x_, y_ + other.y_);
        return ret;
    }

    Vec2 Vec2::operator +=(const Vec2 &other) {
        x_ += other.x_;
        y_ += other.y_;
        return *this;
    }

    Vec2 Vec2::operator *(float v) const {
        Vec2 ret(x_ * v, y_ * v);
        return ret;
    }

    float Vec2::dot(const Vec2 &other) const {
        return x_ * other.x_ + y_ * other.y_;
    }

    }
}
