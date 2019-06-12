#ifndef GRAPHICS_TRANSMAT4_H
#define GRAPHICS_TRNASMAT4_H
#include "graphicsglobal.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {
    class TransMat4 {
        TransMat4();
        TransMat4(float *d);

        TransMat4 operator *(TransMat4 &other);

        static TransMat4 identity();

        static TransMat4 translation(float Tx, float Ty, float Tz);
        static TransMat4 translation(Vec3 &vec3);

        static TransMat4 rotation(float Rz, float Ry, float Rz, float r);
        static TransMat4 rotation(Vec3 &vec3, float r);

        static TransMat4 projection(float aspect, float fov, float zNear, float zFar);

        static TransMat4 lookAt(const Vec3 &position, const Vec3 &front, const Vec3 &up);

    public:
        float data[16];
    };
    }
}

#endif
