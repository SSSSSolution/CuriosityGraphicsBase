#ifndef GRAPHICS_CUBE_H
#define GRAPHICS_CUBE_H

#include "observer.h"
#include "worldbaseobject.h"
#include "texture2d.h"

namespace curiosity {
    namespace graphics {

    class CubeObject : public WorldBaseObject, public Observer {
    public:
        CubeObject(const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                   const Vec3 &scaleFactor = Vec3(1.0f, 1.0f, 1.0f),
                   Program *program = NULL);
        virtual ~CubeObject();

        virtual void draw();
        virtual void update(Subject *);

        void setTexture(std::string name);
        void setVelocity(const Vec3 &v) { velocity = v; }
        const Vec3 &getVelocity() const { return velocity; }
        void go(float deltaTime) { move(velocity*deltaTime); }

    private:
        Texture2D texture;
        GLuint vao, vbo;
        Vec3 velocity;
    };

    }
}

#endif
