#ifndef GRAPHICS_LINE3_SEGMENT_H
#define GRAPHICS_LINE3_SEGMENT_H
#include "point3.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class Line3Segment {
    public:
        Line3Segment() {}
        Line3Segment(const Point3 &point, const Vec3 &direction);

        Point3 closestPoint(const Point3 &Q);
        float closestDistanceSquared(const Point3 &Q);

    private:
        Point3 point;
        Vec3 direction;
    };

    }
}

#endif
