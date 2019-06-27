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

    class Font {
    public:
        Font(const char *font);
        void setFactory(CharacterFactory *fac);
        virtual void ~Font();

        Character *getCharacter(wchar_t c);

    private:
        CharacterFactory *factory;
        std::map<wchar_t, Character *> characters;
        std::string fontPath;
    };

    }
}

#endif
