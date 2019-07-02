#ifndef GRAPHICS_LINE3_H
#define GRAPHICS_LINE3_H
#include "graphicsglobal.h"
#include "math/point3.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class Line3 {
    public:
        Line3() {}
        Line3(const Point3 &origin, const Vec3 &direction);

        // 返回直线上离Q点最近的点
        Point3 closestPoint(const Point3 &Q);
        // 和点Q的最近距离
        float closestDistanceSquared(const Point3 &Q);
        // 返回离直线最近的点
        std::pair<Point3, Point3> closestPoint(const Line3 &line);
        // 返回两条直线的最近距离
        float closestDistanceSquared(const Line3 &line);

    private:
        Point3 origin;
        Vec3 direction;
    };

    }
}

#endif
