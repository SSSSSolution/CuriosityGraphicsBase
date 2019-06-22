#include <iostream>
#include "spriterender.h"
#include "transmat4.h"

namespace curiosity {
    namespace graphics {

    SpriteRender::SpriteRender(Program &p) {
        program = p;
        initRenderData();
    }

    SpriteRender::~SpriteRender() {
        glDeleteVertexArrays(1, &quadVAO);
    }

    void SpriteRender::drawSprite(Texture2D &texture, Vec2 position,
                                  Vec2 size, GLfloat r, Vec3 color) {
        program.use();
        TransMat4 model = TransMat4::translation(position.x_, position.y_, 0.0f);
        TransMat4 trans1 = TransMat4::translation(0.5f*size.x_, 0.5f * size.y_, 0.0f);
        TransMat4 rotate = TransMat4::rotation(0.0f, 0.0f, 1.0f, r);
        TransMat4 trans2 = TransMat4::translation(-0.5f*size.x_, -0.5f * size.y_, 0.0f);
        TransMat4 scale = TransMat4::scale(size.x_, size.y_, 1.0f);

        model = model * trans1* rotate *trans2 * scale;

        program.setTransMat4("model", model);
        program.setVec3("spriteColor", color);

        glActiveTexture(GL_TEXTURE0);
        texture.bind();

        glBindVertexArray(quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

    void SpriteRender::initRenderData() {
        GLuint VBO;
        GLfloat vertices[] = {
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };

        glGenVertexArrays(1, &quadVAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(quadVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }



    }
}

