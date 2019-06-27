#include "font.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    Font::Font(const char *font)
        : factory(factory) {
        fontPath = fontDir() + font;
    }

    Font::~Font() {
        for (auto iter : characters) {
            if (*iter) {
                delete (*iter);
            }
        }
    }

    void Font::setFactory(CharacterFactory *fac) {
        factory = fac;
    }

    Character *Font::getCharacter(wchar_t c) {
        Character *character;

        auto iter = characters.find(c);
        if (iter != characters.end()) {
            character = characters[c];
        } else {
            character = factory->createCharacter(fontPath, c);
            characters.insert(pair<string, Character *>(c, character));
        }
        return character;
    }

    }
}
