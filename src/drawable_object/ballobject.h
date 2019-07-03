#ifndef GRAPHICS_BALL_OBJECT_H
#define GRAPHICS_BALL_OBJECT_H
#include "observer.h"
#include "worldbaseobject.h"
#include "vec3.h"

namespace curiosity {
    namespace graphics {

    class BallObject : public WorldBaseObject, public Observer {
    public:
        BallObject(const Vec3 &position = Vec3(0.0f, 0.0f, 0.0f),
                   const Vec3 &scaleFactor = Vec3(1.0f, 1.0f, 1.0f),
                   Program *program = NULL);
        virtual ~BallObject();

        virtual void draw();
        virtual void update(Subject *);

        void setVeocity(const Vec3 &v) { velocity = v; }
        const Vec3 &getVelocity() const { return velocity; }
        void go(float deltaTime) { move(velocity*deltaTime); }

    private:
        unsigned int vertCount;

        GLuint vao, vbo;
        Vec3 velocity;
    };

    }
}






#endif
