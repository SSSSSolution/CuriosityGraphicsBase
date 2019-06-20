#ifndef GRAPHICS_TRANSMAT4_H
#define GRAPHICS_TRANSMAT4_H
#include "graphicsglobal.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {
    /* 提供基本的3D图形学转换矩阵 */
    class TransMat4 {
    public:
        TransMat4();
        TransMat4(float *d);

        TransMat4 operator *(TransMat4 &other);

        static TransMat4 identity();

        static TransMat4 translation(float Tx, float Ty, float Tz);
        static TransMat4 translation(Vec3 &vec3);

        static TransMat4 rotation(float Rx, float Ry, float Rz, float r);
        static TransMat4 rotation(Vec3 &vec3, float r);

        static TransMat4 scale(float Rx, float Ry, float Rz);
        static TransMat4 scale(Vec3 &vec3);

        static TransMat4 projection(float aspect, float fov, float zNear, float zFar);

        static TransMat4 lookAt(const Vec3 &position, const Vec3 &front, const Vec3 &up);

    public:
        float data_[16];
    };
    }
}

#endif
