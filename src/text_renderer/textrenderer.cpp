#include "textrenderer.h"
#include "fontmanager.h"
#include "resourcemanager.h"

namespace curiosity {
    namespace graphics {

    TextRenderer::TextRenderer(const char *fontPath, CharacterFactory *factory)
        : factory(factory) {
        font = FontManager::instance()->getFont(fontPath, factory);
    }

    TextRenderer::~TextRenderer() {
        if (factory)
            delete factory;
        // font 由fontManager 管理
    }

    }
}
