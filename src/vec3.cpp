#include "vec3.h"
#include <cmath>
using namespace std;

namespace curiosity {
    namespace graphics {

    Vec3::Vec3(float x, float y, float z)
        : x_(x), y_(y), z_(z) {
    }

    Vec3 Vec3::normalize() const {
        float sum = x_ * x_ + y_ * y_ + z_ * z_;
        Vec3 ret(x_ < 0 ? -1.0f * sqrt(x_*x_/sum) :  sqrt(x_*x_/sum),
                 y_ < 0 ? -1.0f * sqrt(y_*y_/sum) :  sqrt(y_*y_/sum),
                 z_ < 0 ? -1.0f * sqrt(z_*z_/sum) :  sqrt(z_*z_/sum));
        return ret;
    }

    Vec3 Vec3::operator -(const Vec3 &other) const {
        Vec3 ret(x_ - other.x_, y_ - other.y_, z_ - other.z_);
        return ret;
    }

    Vec3 Vec3::operator +(const Vec3 &other) const {
        Vec3 ret(x_ + other.x_, y_ + other.y_, z_ + other.z_);
        return ret;
    }

    Vec3 Vec3::operator *(const Vec3 &other) const {
        Vec3 ret(x_ * other.x_, y_ * other.y_, z_ * other.z_);
        return ret;
    }

    Vec3 Vec3::operator *(float v) const {
        Vec3 ret(x_ * v, y_ * v, z_ * v);
        return ret;
    }

    float Vec3::dot(const Vec3 &other) const {
        return x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
    }

    Vec3 Vec3::cross(const Vec3 &other) const {
        Vec3 ret(y_ * other.z_ - z_ * other.y_,
                 z_ * other.x_ - x_ * other.z_,
                 x_ * other.y_ - y_ * other.x_);
        return ret;
    }

    }
}
