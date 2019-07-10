#ifndef GRAPHICS_RAY_H
#define GRAPHICS_RAY_H
#include "point3.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class Ray {
    public:
        Ray() {}
        Ray(const Point3 &origin, const Vec3 &direction);

        const Point3 &getOrigin() const { return origin; }
        const Vec3 &getDirection() const { return direction; }

    private:
        Point3 origin;
        Vec3 direction;
    };

    }
}

#endif
