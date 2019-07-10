#include "vec3.h"
#include <cmath>
using namespace std;

namespace curiosity {
    namespace graphics {

    Vec3::Vec3(float x, float y, float z)
        : x(x), y(y), z(z) {
    }

    float Vec3::length() {
        return sqrt(x*x + y*y + z*z);
    }

    Vec3 Vec3::normalize() const {
        float sum = x * x + y * y + z * z;
        Vec3 ret(x < 0 ? -1.0f * sqrt(x*x/sum) :  sqrt(x*x/sum),
                 y < 0 ? -1.0f * sqrt(y*y/sum) :  sqrt(y*y/sum),
                 z < 0 ? -1.0f * sqrt(z*z/sum) :  sqrt(z*z/sum));
        return ret;
    }

    Vec3 Vec3::operator =(const Vec3 &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }

    Vec3 Vec3::operator -(const Vec3 &other) const {
        Vec3 ret(x - other.x, y - other.y, z_ - other.z);
        return ret;
    }

    Vec3 Vec3::operator +(const Vec3 &other) const {
        Vec3 ret(x + other.x, y + other.y, z + other.z);
        return ret;
    }

    Vec3 Vec3::operator +=(const Vec3 &other) {
        *this = *this + other;
        return *this;
    }

    Vec3 Vec3::operator *(const Vec3 &other) const {
        Vec3 ret(x * other.x, y * other.y, z * other.z_);
        return ret;
    }

    Vec3 Vec3::operator *(float v) const {
        Vec3 ret(x * v, y * v, z * v);
        return ret;
    }

    float Vec3::dot(const Vec3 &other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vec3 Vec3::cross(const Vec3 &other) const {
        return Vec3(y * other.z - z * other.y,
                    z * other.x - x * other.z,
                    x * other.y - y * other.x);
    }

    Vec3 operator *(float v, const Vec3 &vec) {
        return (vec * v);
    }

    std::ostream &operator <<(ostream &os, const Vec3 &vec) {
        return os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
    }

    }
}


























