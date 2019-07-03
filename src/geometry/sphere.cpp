#include "geometry/sphere.h"
#include "vec3.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    vector<float> Sphere::genVertexs(float latitudeStep, float longitudeStep) {
        float latitude, longitude; // 纬度, 经度
        float x, y, z, xn, yn, zn;
        vector<float> vertices;

        latitudeStep = RADIANS(latitudeStep);
        longitudeStep = RADIANS(longitudeStep);
        for (latitude = PI/2.0f; latitude > PI/-2.0f; latitude -= latitudeStep) {
            z = sin(latitude);
            float nextLatitude = latitude - latitudeStep;
            if (nextLatitude < PI/-2.0f) {
                nextLatitude = PI/-2.0f;
            }
            zn = sin(nextLatitude);
            for (longitude = 0.0f; longitude < 2.0f*PI + longitudeStep; longitude += longitudeStep) {
                x = cos(latitude) * cos(longitude);
                y = cos(latitude) * sin(longitude);
                xn = cos(nextLatitude) * cos(longitude);
                yn = cos(nextLatitude) * sin(longitude);
                vertices.push_back(x);
                vertices.push_back(y);
                vertices.push_back(z);
                vertices.push_back(xn);
                vertices.push_back(yn);
                vertices.push_back(zn);
            }
        }
        return vertices;
    }

    Sphere::Sphere(const Point3 &origin, float radius)
        : origin(origin), radius(radius) {
    }

    bool Sphere::isIntersect(const Sphere &other) {
        return ((origin - other.origin).dot(origin - other.origin)
                > (radius + other.radius) * (radius + other.radius));
    }

    bool Sphere::isIntersect(const Ray &ray) {

    }




    }
}
