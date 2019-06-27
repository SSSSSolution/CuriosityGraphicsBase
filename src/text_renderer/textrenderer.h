#ifndef GRAPHICS_TEXT_RENDERER_H
#define GRAPHICS_TEXT_RENDERED_H

/* Interface of text rendering.
 *
 *  author: HuangWei
 *  mail:   1845739048@qq.com
 *  date:   2019-6-27
 */

#include <string>
#include "graphicsglobal.h"
#include "vec3.h"
#include "font.h"

namespace curiosity {
    namespace graphics {
    class Character;
    class CharacterFactory;

    class TextRenderer {
    public:
        TextRenderer(const char *fontPath);
        virtual ~TextRenderer() = 0;
        virtual void renderText(std::string text, float x, float y, float scale, Vec3 color) = 0;

    protected:
        Font *font;
    };

    class Character {
    public:
        virtual ~Character() = 0;
    };

    class CharacterFactory {
    public:
        virtual Character *createCharacter(const std::string &fontPath, wchar_t ch);
    };

    }
}

#endif
