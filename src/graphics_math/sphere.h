#ifndef GRAPHICS_SPHERE_H
#define GRAPHICS_SPHERE_H

/* 球体
 *
 * Author:  HuangWei
 * Date:    2019-7-3
 */
#include "graphicsglobal.h"
#include "point3.h"
#include <vector>

namespace curiosity {
    namespace graphics {
    class Ray;

    class Sphere {
    public:
        // 生成球体的顶点数据, 球心为原点，半径为1.0f
        static std::vector<float> genVertexs(float latitudeStep, float longitudeStep);

        Sphere() {}
        Sphere(const Point3 &origin, float radius);

        const Point3 &getOrigin() const { return origin; }
        float getRadius() const { return radius; }

        // 检测相交
        bool isIntersect(const Sphere &other);
        bool isIntersect(const Ray &ray);

    private:
        Point3 origin;
        float radius;
    };

    }
}

#endif
