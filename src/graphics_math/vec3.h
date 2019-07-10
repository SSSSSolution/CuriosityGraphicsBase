#ifndef GRAPHICS_VEC3_H
#define GRAPHICS_VEC3_H
#include <iostream>

namespace curiosity {
    namespace graphics {

    class Vec3 {
    public:
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        float length();

        Vec3 normalize() const;

        Vec3 operator =(const Vec3 &other);

        Vec3 operator -(const Vec3 &other) const;

        Vec3 operator +(const Vec3 &other) const;

        Vec3 operator +=(const Vec3 &other);

        Vec3 operator *(const Vec3 &other) const;

        Vec3 operator *(float v) const;

        float dot(const Vec3 &other) const;

        Vec3 cross(const Vec3 &other) const;

    public:
        float x, y, z;
    };

    Vec3 operator *(float v, const Vec3 &vec);
    std::ostream &operator <<(std::ostream &os, const Vec3 &vec);

    }
}
#endif
