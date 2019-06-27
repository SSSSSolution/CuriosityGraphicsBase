#include "textrenderer.h"
#include "fontmanager.h"

namespace curiosity {
    namespace graphics {

    TextRenderer::TextRenderer(const char *fontPath) {
        font = FontManager::instance()->getFont(fontDir() + fontPath);
    }

    }
}
