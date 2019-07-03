#include "geometry/line3.h"
#include "math.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Line3::Line3(const Point3 &origin, const Vec3 &direction)
        : origin(origin), direction(direction) {
    }

    Point3 Line3::closestPoint(const Point3 &Q) {
        Vec3 w = Q - origin;
        Vec3 projw = (w.dot(direction)/(direction.dot(direction))) * direction;
        return Point3(origin.vec() + projw);
    }

    float Line3::closestDistanceSquared(const Point3 &Q) {
        Vec3 w = Q - origin;
        return (w.dot(w) - w.dot(direction) * w.dot(direction) / direction.dot(direction));
    }

    std::pair<Point3, Point3> Line3::closestPoint(const Line3 &line) const {
        Point3 point1, point2;
        Vec3 w0 = origin - line.origin;
        float a = direction.dot(direction);
        float b = direction.dot(line.direction);
        float c = line.direction.dot(line.direction);
        float d = direction.dot(w0);
        float e = line.direction.dot(w0);

        float denom = a * c - b * b;
        if (IS_FLOAT_ZERO(denom)) {
            point1 = origin;
            point2 = Point3(line.origin.vec() + (e/c) * line.direction);
        } else {
            point1 = Point3(origin.vec() + ((b*e-c*d)/denom) * direction);
            point2 = Point3(line.origin.vec() + ((a*e-b*d)/denom) * line.direction);
        }
        return make_pair(point1, point2);
    }

    float Line3::closestDistanceSquared(const Line3 &line) const {
        Vec3 w0 = origin - line.origin;
        float a = direction.dot(direction);
        float b = direction.dot(line.direction);
        float c = line.direction.dot(line.direction);
        float d = direction.dot(w0);
        float e = line.direction.dot(w0);

        Vec3 wc;
        float denom = a*c - b*b;
        if (IS_FLOAT_ZERO(denom)) {
            wc = w0 - (e/c) * line.direction;
        } else {
            wc = w0 + ((b*e - c*d)/denom) * direction
                    - ((a*e - b*d)/denom) * line.direction;
        }
        return wc.dot(wc);
    }

    }
}


























