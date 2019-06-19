#ifndef GRAPHICS_DRAWABLE_OBJECT_H
#define GRAPHICS_DRAWABLE_OBJECT_H
#include "vec3.h"
#include "program.h"

namespace curiosity {
    namespace graphics {

    class DrawableObject {
    public:
        DrawableObject(const Vec3 &position);
        virtual void draw(Program &program) = 0;

    public:
        Vec3 position_;
    };

    }
}

#endif
