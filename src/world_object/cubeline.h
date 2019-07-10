#ifndef GRAPHICS_CUBE_LINE_H
#define GRAPHICS_CUBE_LINE_H

#include "worldbaseobject.h"
#include "texture2d.h"

namespace curiosity {
    namespace graphics {

    class CubeLine : public WorldBaseObject {
    public:
        CubeLine(const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                   const Vec3 &scaleFactor = Vec3(1.0f, 1.0f, 1.0f),
                   Program *program = NULL);
        virtual ~CubeLine();

        virtual void draw();

        void setVelocity(const Vec3 &v) { velocity = v; }
        const Vec3 &getVelocity() const { return velocity; }
        void go(float deltaTime) { move(velocity*deltaTime); }

    private:
        GLuint vao, vbo;
        Vec3 velocity;
    };

    }
}

#endif
