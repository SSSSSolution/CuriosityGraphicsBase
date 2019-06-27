#include <assert.h>
#include "tttextrenderer.h"
#include "fontmanager.h"
#include "ft2build.h"
#include FT_FREETYPE_H
using namespace std;

namespace curiosity {
    namespace graphics {

    TTTextRenderer::TTTextRenderer(const char *fontPath, float width, float height)
        : TextRenderer(fontPath, new TTCharacterFactory()) {
        program = ResourceManager::loadProgram("/font/ttfont.vs", "/font/ttfont.fs", NULL, "ttfont");
        TransMat4 projection = TransMat4::ortho(0.0f, width,
                                                0.0f, height,
                                                -1.0f, 1.0f);
        program.use();
        program.setTransMat4("projection", projection);
        // 初始化VAO
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6*4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GL_FLOAT), 0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    TTTextRenderer::~TTTextRenderer() {
    }


    void TTTextRenderer::renderText(std::wstring text, float x, float y, float scale, Vec3 color) {
        program.use();
        program.set3f("textColor", color.x_, color.y_, color.z_);
        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);

        wstring::const_iterator c;
        for (c = text.begin(); c != text.end(); ++c) {
            TTCharacter *ch = dynamic_cast<TTCharacter*>(font->getCharacter(*c));
            assert(ch != NULL);

            float xpos = x + ch->bearing.x_ * scale;
            float ypos = y - (ch->size.y_ - ch->bearing.y_) * scale;

            float w = ch->size.x_ * scale;
            float h = ch->size.y_ * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos,     ypos,       0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 1.0f },

                { xpos,     ypos + h,   0.0f, 0.0f },
                { xpos + w, ypos,       1.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f }
            };
            glBindTexture(GL_TEXTURE_2D, ch->textureID);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x += (ch->advance >> 6) * scale;
        }
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    TTCharacter *TTCharacterFactory::createCharacter(const std::string &fontPath, wchar_t ch) {
        std::cout << __func__ << endl;
        FT_Library ft;
        if (FT_Init_FreeType(&ft))
            cout << "Error:: freetype: could not init freetype lib" << endl;
        FT_Face face;
        if (FT_New_Face(ft, (fontPath.c_str()), 0, &face))
            cout << "Error:: freetype: failed to load font:" << fontPath << endl;
        FT_Set_Pixel_Sizes(face, 0, 50);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        if (FT_Load_Char(face, ch, FT_LOAD_RENDER))
            cout << "Error:: freetype: failed to load Glyph" << endl;
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width,
                     face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE,
                     face->glyph->bitmap.buffer);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        TTCharacter *character =  new TTCharacter(texture,
                                                  Vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                                                  Vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                                                  (GLuint)(face->glyph->advance.x));
        glBindTexture(GL_TEXTURE_2D, 0);
        FT_Done_Face(face);
        FT_Done_FreeType(ft);

        return character;
    }

    TTCharacter::TTCharacter(unsigned int textureID, Vec2 size, Vec2 bearing, unsigned int advance)
        : textureID(textureID), size(size), bearing(bearing), advance(advance) {
    }

    TTCharacter::~TTCharacter() {
        glDeleteTextures(1, &textureID);
    }

    }
}





















