#ifndef GRAPHICS_POINT_H
#define GRAPHICS_POINT_H
#include "vec3.h"
#include <iostream>

namespace curiosity {
    namespace graphics {

    class Point3 {
    public:
        Point3() {}
        Point3(const Vec3 &point);

        const Vec3 &vec() const { return point; }
        // 两点相减得向量
        Vec3 operator -(const Point3 &other) const;

    private:
        Vec3 point;
    };

    std::ostream &operator <<(std::ostream &io, const Point3 &p);

    }
}

#endif
