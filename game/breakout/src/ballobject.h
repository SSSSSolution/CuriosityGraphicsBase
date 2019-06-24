#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H
#include "graphicsglobal.h"
#include "gameobject.h"
#include "vec2.h"

namespace curiosity {
    namespace graphics {

    class BallObject : public GameObject {
    public:
        BallObject();
        BallObject(Vec2 pos, float radius, Vec2 velocity, Texture2D sprite);

        Vec2 move(float dt, unsigned int windowWidth);
        void reset(Vec2 position, Vec2 velocity);
    public:
        float radius;
        bool stuck;
    };

    }
}

#endif
