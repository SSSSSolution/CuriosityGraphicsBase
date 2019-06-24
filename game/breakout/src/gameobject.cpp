#include "gameobject.h"

namespace curiosity {
    namespace graphics {

    GameObject::GameObject()
        : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f),
          color(1.0f, 1.0f, 1.0f), rotation(0.0f), sprite(),
          isSolid(false), destroyed(false) {
    }

    GameObject::GameObject(Vec2 pos, Vec2 size, Texture2D sprite, Vec3 color, Vec2 velocity)
        : position(pos), size(size), velocity(velocity),
          sprite(sprite), color(color), rotation(0.0f),
          isSolid(false), destroyed(false) {
    }

    void GameObject::draw(SpriteRender &render) {
        render.drawSprite(sprite, position, size, rotation, color);
    }

    }
}
