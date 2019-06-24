#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "graphicsglobal.h"
#include "vec2.h"
#include "vec3.h"
#include "texture2d.h"
#include "spriterender.h"

namespace curiosity {
    namespace graphics {

    class GameObject {
    public:
        GameObject();
        GameObject(Vec2 pos, Vec2 size, Texture2D sprite,
                   Vec3 color = Vec3(1.0f,1.0f, 1.0f), Vec2 velocity= Vec2(0.0f, 0.0f));

        virtual void draw(SpriteRender &render);
    public:
        Vec2 position, size, velocity;
        Vec3 color;
        GLfloat rotation;
        GLboolean isSolid;
        GLboolean destroyed;
        Texture2D sprite;
    };

    }
}

#endif
