#include "font.h"

using namespace std;

namespace curiosity {
    namespace graphics {

    Font::Font(const char *font, CharacterFactory *factory)
        : factory(factory) {
        fontPath = fontDir() + font;
    }

    Font::~Font() {
        for (auto iter : characters) {
            if (iter.second) {
                delete (iter.second);
            }
        }
    }

    Character *Font::getCharacter(char c) {
        Character *character;

        auto iter = characters.find(c);
        if (iter != characters.end()) {
            character = characters[c];
        } else {
            cout << c << endl;
            character = factory->createCharacter(fontPath, c);
            characters.insert(pair<char, Character *>(c, character));
        }
        return character;
    }

    }
}
