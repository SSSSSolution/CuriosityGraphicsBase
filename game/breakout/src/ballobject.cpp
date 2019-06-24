#include "ballobject.h"

namespace curiosity {
    namespace graphics {

    BallObject::BallObject()
        : radius(12.5f), stuck(true) {
    }

    BallObject::BallObject(Vec2 pos, float radius, Vec2 velocity, Texture2D sprite)
        : GameObject(pos, Vec2(radius*2, radius*2), sprite, Vec3(1.0f, 1.0f, 1.0f), velocity),
          radius(radius), stuck(true) {
    }

    Vec2 BallObject::move(float dt, unsigned int windowWidth) {
        if (!stuck) {
            position += velocity * dt;

            if (position.x_ < 0.0f) {
                velocity.x_ = -velocity.x_;
                position.x_ = 0.0f;
            } else if (position.x_ + size.x_ > windowWidth) {
                velocity.x_ = -velocity.x_;
                position.x_ = windowWidth - size.x_;
            }
            if (position.y_ <= 0.0f) {
                velocity.y_ = -velocity.y_;
                position.y_ = 0.0f;
            }
        }
        return position;
    }

    void BallObject::reset(Vec2 pos, Vec2 vel) {
        position = pos;
        velocity = vel;
        stuck = true;
    }

    }
}
