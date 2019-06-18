#ifndef GRAPHICS_DRAWABLE_OBJECT_H
#define GRAPHICS_DRAWABLE_OBJECT_H
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class DrawableObject {
    public:
        DrawableObject(const Vec3 &position);
        virtual void draw() = 0;

    protected:
        Vec3 position_;
    };

    }
}

#endif
