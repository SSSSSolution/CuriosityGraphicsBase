#ifndef GRAPHICS_VEC2_H
#define GRAPHICS_VEC2_H

namespace curiosity {
    namespace graphics {

    class Vec2 {
    public:
        Vec2(float x = 0.0f, float y = 0.0f);

        Vec2 normalize() const;

        Vec2 operator -(const Vec2 &other) const;

        Vec2 operator -=(const Vec2 &other);

        Vec2 operator +(const Vec2 &other) const;

        Vec2 operator +=(const Vec2 &other);

        Vec2 operator *(float v) const;

        float dot(const Vec2 &other) const;

    public:
        float x, y;
    };

    }
}

#endif
