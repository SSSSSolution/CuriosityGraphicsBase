#ifndef GRAPHICS_VEC4_H
#define GRAPHICS_VEC4_H

namespace curiosity {
    namespace graphics {

    class Vec4 {
    public:
        Vec4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);

    public:
        float x, y, z, w;
    };

    }
}

#endif
