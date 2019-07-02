#include "point3.h"

namespace curiosity {
    namespace graphics {

    Point3::Point3(const Vec3 &point)
        : point(point) {
    }

    Vec3 Point3::operator -(const Point3 &other) const {
        return (point - other.point);
    }

    std::ostream &operator <<(std::ostream &io, const Point3 &p) {
        return io << "point: " << p.vec();
    }

    }
}
