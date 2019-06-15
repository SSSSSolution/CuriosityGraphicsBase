#ifndef GRAPHICS_VEC3_H
#define GRAPHICS_VEC3_H

namespace curiosity {
    namespace graphics {

    class Vec3 {
    public:
        Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

        Vec3 normalize() const;

        Vec3 operator -(const Vec3 &other) const;

        Vec3 operator +(const Vec3 &other) const;

        Vec3 operator *(const Vec3 &other) const;

        Vec3 operator *(float v) const;

        float dot(const Vec3 &other) const;

        Vec3 cross(const Vec3 &other) const;

    public:
        float x_, y_, z_;
    };

    }
}
#endif
