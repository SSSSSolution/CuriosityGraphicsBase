#ifndef GRAPHICS_WORLD_BASE_OBJECT_H
#define GRAPHICS_WORLD_BASE_OBJECT_H

#include "program.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class WorldBaseObject {
    public:
        WorldBaseObject(const Vec3 &position, const Vec3 &scaleFactor, Program *program);
        virtual ~WorldBaseObject() = 0;

        virtual void translate(const Vec3 &trans);
        virtual void scale(const Vec3 &scaleFactor);

        virtual void draw() = 0;

    private:
        void setModelMatrix();

    protected:
        Program *program;
        Vec3 position;
        Vec3 scaleFactor;
    };

    }
}

#endif
