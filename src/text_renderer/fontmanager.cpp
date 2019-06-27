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
            delete *iter;
    }

    Font *FontManager::getFont(const std::string &name) {
        Font *font;
        auto iter = fonts.find(name);
        if (iter == fonts.end()) {
            font = new Font(name);
            fonts.insert(make_pair<string, Font*>(name, font));
        } else {
            font = *iter;
        }

        return font;
    }


    }
}

