#include "line3segment.h"

namespace curiosity {
    namespace graphics {

    Line3Segment::Line3Segment(const Point3 &point, const Vec3 &direction)
        : point(point), direction(direction) {
    }

    Point3 Line3Segment::closestPoint(const Point3 &Q) {
        Vec3 w = Q - point;
        float proj = direction.dot(w);

        if (proj <= 0) {
            return point;
        } else {
            float vsq = direction.dot(direction);
            if (proj >= vsq) {
                return Point3(point.vec() + direction);
            } else {
                return Point3(point.vec() + proj/vsq*direction);
            }
        }
    }

    float Line3Segment::closestDistanceSquared(const Point3 &Q) {
        Vec3 w = Q - point;
        float proj = direction.dot(w);

        if (proj <= 0) {
            return w.dot(w);
        } else {
            float vsq = direction.dot(direction);
            if (proj >= vsq) {
                return (w-direction).dot(w-direction);
            } else {
                return w.dot(w) - proj * proj / vsq;
            }
        }
    }

    }
}

