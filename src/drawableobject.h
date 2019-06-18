#ifndef GRAPHICS_DRAWABLE_OBJECT_H
#define GRAPHICS_DRAWABLE_OBJECT_H
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class DrawableObject {
    public:
        DrawableObject(Vec3 &position, unsigned int length);
        virtual void drawEnable(bool b) = 0;

    protected:
        Vec3 position_;
        unsigned int length_;
    };

    }
}

#endif
