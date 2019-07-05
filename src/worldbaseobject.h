#ifndef GRAPHICS_WORLD_BASE_OBJECT_H
#define GRAPHICS_WORLD_BASE_OBJECT_H

#include "program.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class WorldBaseObject {
    public:
        WorldBaseObject(const Vec3 &position, const Vec3 &scaleFactor, Program *program);
        virtual ~WorldBaseObject() {}

        virtual void move(const Vec3 &trans);
        virtual void scale(const Vec3 &scaleFactor);

        virtual void draw() = 0;

        void setPosition(const Vec3 &pos) { position = pos; }
        const Vec3 &getPosition() const { return position; }
        Program *getProgram() { return program; }

    protected:
        void setModelMatrix();

    protected:
        Program *program;
        Vec3 position;
        Vec3 scaleFactor;
    };

    }
}

#endif
