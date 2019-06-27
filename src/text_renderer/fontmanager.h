#ifndef GRAPHICS_FONT_MANAGER_H
#define GRAPHICS_FONT_MANAGER_H

#include <map>
#include "font.h"

/* Used to manager fonts' resource
 *
 */

namespace curiosity {
    namespace graphics {

    class FontManager {
    public:
        FontManager *instance();
        ~FontManager();
        Font *getFont(const std::string &name);

    private:
        static FontManager *fontManager;
        FontManager() {}
        FontManager(FontManager &) {}

    private:
        std::map<std::string, Font *> fonts;
    };

    }
}

#endif
