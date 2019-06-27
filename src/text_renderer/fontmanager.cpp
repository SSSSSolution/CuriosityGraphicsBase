#include <string>
#include "fontmanager.h"
using namespace std;

namespace curiosity {
    namespace graphics {

    FontManager *FontManager::fontManager = NULL;

    FontManager *FontManager::instance() {
        if (fontManager == NULL) {
            fontManager = new FontManager;
        }
        return fontManager;
    }

    FontManager::~FontManager() {
        for (auto iter : fonts)
            delete iter.second;
    }

    Font *FontManager::getFont(const char *name, CharacterFactory *factory) {
        Font *font;
        auto iter = fonts.find(name);
        if (iter == fonts.end()) {
            font = new Font(name, factory);
            fonts.insert(pair<string, Font*>(name, font));
        } else {
            font = (*iter).second;
        }

        return font;
    }


    }
}

