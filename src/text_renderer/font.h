#ifndef GRAPHICS_FONT_H
#define GRAPHICS_FONT_H

/* Used to gen character.
 * Use flyweight pattern.
 *
 * Author:  HuangWei
 * Emai:    1845739048@qq.com
 * Date:    2019-6-27
 */

#include <map>
#include "graphicsglobal.h"

namespace curiosity {
    namespace graphics {
    class Character;
    class CharacterFactory;

    class Font {
    public:
        Font(const char *font, CharacterFactory *factory);
        virtual ~Font();

        Character *getCharacter(wchar_t c);

    private:
        CharacterFactory *factory;
        std::map<wchar_t, Character *> characters;
        std::string fontPath;
    };

    class Character {
    public:
        virtual ~Character() {}
    };

    class CharacterFactory {
    public:
        virtual ~CharacterFactory() {}
        virtual Character *createCharacter(const std::string &fontPath, wchar_t ch) = 0;
    };

    }
}

#endif
