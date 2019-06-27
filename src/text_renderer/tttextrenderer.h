#ifndef GRAPHICS_TTTEXT_RENDERER_H
#define GRAPHICS_TTTEXT_RENDERER_H

/*  True type font text renderer.
 *  Use flyweight pattern and factory pattern.
 *
 *  实现一种新的字体格式的渲染需要实现下面这三个类
 *
 *　! 与OpenGL紧耦合
 *  ! 与freetype紧耦合
 *
 *  Author: HuangWei
 *  Mail:   1845739048@qq.com
 *  Date:   2019-6-27
 */

#include <map>
#include "graphicsglobal.h"
#include "textrenderer.h"
#include "vec2.h"
#include "font.h"
#include "resourcemanager.h"

namespace curiosity {
    namespace graphics {

    class TTCharacter;
    class TTCharacterFactory;

    class TTTextRenderer : public TextRenderer {
    public:
        TTTextRenderer(const char *fontPath, float width, float height);
        virtual ~TTTextRenderer();
        virtual void renderText(std::wstring text, float x, float y, float scale, Vec3 color);

    private:
        Program program;
        GLuint VAO, VBO;
        TTCharacterFactory *charFactory;
    };

    class TTCharacter : public Character {
    public:
        TTCharacter(unsigned int textureID, Vec2 size, Vec2 bearing, unsigned int advance);
        ~TTCharacter();

        unsigned int textureID;
        Vec2 size;
        Vec2 bearing;
        unsigned int advance;
    };

    class TTCharacterFactory : public CharacterFactory {
    public:
        virtual TTCharacter *createCharacter(const std::string &fontPath, wchar_t ch);
    };

    }
}

#endif
