#ifndef SPRITE_RENDER_H
#define SPRITE_RENDER_H
#include "graphicsglobal.h"
#include "program.h"
#include "texture2d.h"
#include "vec2.h"

namespace curiosity {
    namespace graphics {

    class SpriteRender {
    public:
        SpriteRender(Program &program);
        ~SpriteRender();

        void drawSprite(Texture2D &texture, Vec2 position,
                        Vec2 size = Vec2(10.0f, 10.0f), GLfloat rotate = 0.0f,
                        Vec3 color = Vec3(1.0f, 1.0f, 1.0f));

    private:
        void initRenderData();

    private:
        Program program;
        GLuint quadVAO;
    };

    }
}

#endif
